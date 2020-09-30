#type VERTEX
#version 450 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec4 a_Color;
layout(location = 2) in vec2 a_TexCoord;
layout(location = 3) in vec3 a_Normal;

uniform mat4 u_ViewProjection;
uniform mat4 u_View;
uniform mat4 u_Model;

out vec4 v_Color;
out vec3 v_Normal;
out vec2 v_TexCoord;
out vec3 v_Position;
			
void main()
{	
	v_Color = a_Color;
	v_Normal = ( u_View * u_Model * vec4(a_Normal, 0.0f)).xyz;
	v_TexCoord = a_TexCoord;
	v_Position =   (u_Model * vec4(a_Position, 1.0f)).xyz;
	gl_Position =  u_ViewProjection * u_Model * vec4(a_Position, 1.0);
}


#type FRAGMENT
#version 450 core

struct Material
{

	sampler2D diffuseTexture;
	sampler2D specularTexture;
	sampler2D emissionTexture;

	vec3 ambient;
	vec3 diffuse;
	vec3 emission;
	vec3 specular;

	float opacity;
	bool cutoff;
	bool useTextureAsAlpha;
	bool doublesided;

	float shininess;

	vec2 tiling;
};

struct DirectionalLight
{
	vec3 direction;
	vec3 color;
	float brightness;
};

struct PointLight
{
	vec3 position;
	vec3 color;
	float constant;
	float linear;
	float quadratic;
	float brightness;
};

struct SpotLight
{
	vec3 position;
	vec3 direction;
	vec3 color;
	float cutoff;
	float outerCutoff;
	float constant;
	float linear;
	float quadratic;
	float brightness;
};

uniform Material material;

//Lights
uniform int numPointLights;
uniform int numDirLights;
uniform int numSpotLights;

#define NR_LIGHTS 20

uniform DirectionalLight directionalLights[NR_LIGHTS];
uniform PointLight pointLights[NR_LIGHTS];
uniform SpotLight spotLights[NR_LIGHTS];

uniform vec3 CameraPosition;

in vec4 v_Color;
in vec3 v_Normal;
in vec2 v_TexCoord;
in vec3 v_Position;

layout(location = 0) out vec4 color;

float gamma = 2.2;
vec3 CalcDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDirection, vec2 texCoord);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDirection, vec2 texCoord);
vec3 CalculateSpotLight(SpotLight light, vec3 normal, vec3 FragPos, vec3 viewDirection, vec2 texCoord);

void main()
{
	vec3 normal = normalize(v_Normal);

	if(material.doublesided)
	{
		if(gl_FrontFacing == false)
		{
			normal = -normalize(v_Normal);
		}
	}

	vec3 viewDirection = normalize(CameraPosition - v_Position);
	vec3 result = vec3(0.0);

	for(int i = 0; i < numDirLights; i++)
	{
		result += CalcDirectionalLight(directionalLights[i], normal, viewDirection, v_TexCoord * material.tiling);
	}

	for(int i = 0; i < numPointLights; i++)
	{
		result += CalcPointLight(pointLights[i], normal, v_Position, viewDirection, v_TexCoord * material.tiling);
	}
	
	for(int i = 0; i < numSpotLights; i++)
	{
		result += CalculateSpotLight(spotLights[i], v_Normal, v_Position, viewDirection, v_TexCoord * material.tiling);
	}

	vec4 emission = texture(material.emissionTexture, v_TexCoord * material.tiling) * vec4(material.emission, 0.0);
	vec4 ambient = vec4(material.ambient, 0.0);
	float alpha = material.useTextureAsAlpha ? texture(material.diffuseTexture, v_TexCoord * material.tiling).a : material.opacity;

	if(material.cutoff == true && alpha < 0.1)
	{
		discard;
	}

	float gamma = 2.2;
	color = ambient + emission + vec4(pow(result, vec3(1.0/gamma)), alpha);
}

vec3 CalcDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDirection, vec2 texCoord)
{
	vec3 lightDir = normalize(light.direction);

	//diffuse shading
	float diff = max(dot(normal, lightDir), 0.0f);

	//spec shading
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDirection, reflectDir), 0.0f), material.shininess);

	
	//combine
	vec3 diffuse = diff * pow(texture(material.diffuseTexture, texCoord).rgb, vec3(gamma)) * material.diffuse;
	vec3 specular = spec * vec3(texture(material.specularTexture, texCoord)) * material.specular;
	return (diffuse + specular) * light.color * light.brightness;
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDirection, vec2 texCoord)
{	
	vec3 lightDirection = normalize(light.position - fragPos);

	//diffuse shading
	float diff = max(dot(normal, lightDirection), 0.0f);

	//specular shading 
	vec3 Reflection = reflect(-lightDirection, normal);
	float spec = pow(max(dot(viewDirection, Reflection), 0.0), material.shininess);
	
	//for PointLight
	float distance = length(light.position - fragPos);
	float attenuation = 1.0f / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

	vec3 diffuse =	diff *	pow(texture(material.diffuseTexture, texCoord).rgb, vec3(gamma)) * material.diffuse;
	vec3 specular = spec *	vec3(texture(material.specularTexture, texCoord)) * material.specular ;


	specular *= attenuation;
	diffuse *= attenuation;

	return (diffuse + specular) * light.color * light.brightness;
}

vec3 CalculateSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDirection, vec2 texCoord)
{

	vec3 lightDirection = normalize(light.position - fragPos);

	//for spotlight
	float theta = dot(lightDirection, normalize(-light.direction));
	float epsilon = light.cutoff - light.outerCutoff;
	float intensity = clamp((theta - light.outerCutoff) / epsilon, 0.0f, 1.0f);

	//diffuse shading
	float diff = max(dot(normal, lightDirection), 0.0f);

	//specular shading	
	vec3 Reflection = reflect(-lightDirection, normal);
	float spec = pow(max(dot(viewDirection, Reflection), 0.0), material.shininess);

	vec3 diffuse = diff * light.color * pow(texture(material.diffuseTexture, texCoord).rgb, vec3(gamma)) * material.diffuse * light.brightness;
	vec3 specular = spec * light.color * vec3(texture(material.specularTexture, texCoord)) * material.specular * light.brightness;
	
	diffuse *= intensity;
	specular *= intensity;

	float distance = length(light.position - fragPos);
	float attenuation = 1.0f / (light.constant + light.linear * distance + light.quadratic * (distance * distance));


	specular *= attenuation;
	diffuse *= attenuation;

	return (diffuse + specular) * light.color * light.brightness;
}