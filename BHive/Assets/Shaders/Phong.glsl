#type VERTEX
#version 450 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec4 a_Color;
layout(location = 2) in vec2 a_TexCoord;
layout(location = 3) in vec3 a_Normal;

uniform mat4 u_ViewProjection;
uniform mat4 u_Model;

out vec4 v_Color;
out vec3 v_Normal;
out vec2 v_TexCoord;
out vec3 v_Position;
			
void main()
{	
	v_Color = a_Color;
	v_Normal = a_Normal;
	v_TexCoord = a_TexCoord;
	v_Position =  a_Position;
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

	float transparency;
	float shininess;

	vec2 tiling;
};


struct Light 
{
	vec3 position;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
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

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float constant;
	float linear;
	float quadratic;
};

struct SpotLight
{
	vec3 position;
	vec3 direction;
	float cutoff;
	float outerCutoff;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

uniform Material material;

uniform DirectionalLight directionalLight;
#define NR_POINT_LIGHTS 4
uniform PointLight pointLights[NR_POINT_LIGHTS];
uniform SpotLight spotLight;

uniform vec3 CameraPosition;

in vec4 v_Color;
in vec3 v_Normal;
in vec2 v_TexCoord;
in vec3 v_Position;

layout(location = 0) out vec4 color;

vec3 CalcDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDirection, vec2 texCoord);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDirection, vec2 texCoord);
vec3 CalculateSpotLight(SpotLight light, vec3 normal, vec3 FragPos, vec3 viewDirection, vec2 texCoord);

void main()
{
	vec3 normal = normalize(v_Normal);
	vec3 viewDirection = normalize(CameraPosition - v_Position);

	vec3 result = CalcDirectionalLight(directionalLight, normal, viewDirection, v_TexCoord * material.tiling);

	//for(int i = 0; i < NR_POINT_LIGHTS; i++)
	//{
	//	result += CalcPointLight(pointLights[i], normal, v_Position, viewDirection, v_TexCoord * material.tiling);
	//}
	//
	//result += CalculateSpotLight(spotLight, v_Normal, v_Position, viewDirection, v_TexCoord * material.tiling);

	color = vec4(result, material.transparency);
}

vec3 CalcDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDirection, vec2 texCoord)
{
	vec3 lightDir = normalize(light.direction);

	//diffuse shading
	float diff = max(dot(normal, lightDir), 0.0f);

	//spec shading
	vec3 reflectDir = reflect(lightDir, normal);
	float spec = pow(max(dot(viewDirection, reflectDir), 0.0f), material.shininess);

	//combine
	vec3 ambient = light.color * material.ambient;
	vec3 diffuse = light.color * diff * vec3(texture(material.diffuseTexture, texCoord)) * material.diffuse * light.brightness;
	vec3 specular = light.color * spec * vec3(texture(material.specularTexture, texCoord)) * material.specular;
	vec3 emission = vec3(texture(material.emissionTexture, texCoord)) * material.emission;
	return ambient  + emission + diffuse + specular ;
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
	float attenuation = 1.0f / (light.constant + (light.linear * distance) + (light.quadratic * (distance * distance)));

	vec3 ambient =  light.ambient	*	material.ambient;
	vec3 diffuse =	light.diffuse	*	diff *	vec3(texture(material.diffuseTexture, texCoord)) * material.diffuse;
	vec3 specular = light.specular	*	spec *	vec3(texture(material.specularTexture, texCoord)) * material.specular;
	vec3 emission = vec3(texture(material.emissionTexture, texCoord)) * material.emission;

	ambient *= attenuation;
	specular *= attenuation;
	diffuse *= attenuation;

	return ambient + diffuse + specular + emission;
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

	vec3 ambient = light.ambient * material.ambient;
	vec3 diffuse = diff * light.diffuse * vec3(texture(material.diffuseTexture, texCoord)) * material.diffuse;
	vec3 specular = spec * light.specular * vec3(texture(material.specularTexture, texCoord)) * material.specular;
	vec3 emission = vec3(texture(material.emissionTexture, texCoord)) * material.emission;

	diffuse *= intensity;
	specular *= intensity;

	return ambient + diffuse + specular + emission;
}