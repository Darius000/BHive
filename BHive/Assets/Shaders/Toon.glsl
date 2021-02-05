#type VERTEX
#version 450 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec4 a_Color;
layout(location = 2) in vec2 a_TexCoord;
layout(location = 3) in vec3 a_Normal;

layout(std140) uniform Matrices
{
	mat4 u_ViewProjection;
	mat4 u_View;
	vec3 u_CameraPosition;
};

uniform mat4 u_Model;

out VS_OUT
{
	vec4 v_Color;
	vec3 v_Normal;
	vec2 v_TexCoord;
	vec3 v_Position;
	vec3 v_CameraPosition;
} vs_out;
			
void main()
{	
	vs_out.v_Color = a_Color;
	vs_out.v_Normal = ( u_View * u_Model * vec4(a_Normal, 0.0f)).xyz;
	vs_out.v_TexCoord = a_TexCoord;
	vs_out.v_Position =   (u_Model * vec4(a_Position, 1.0f)).xyz;
	vs_out.v_CameraPosition = u_CameraPosition;

	gl_Position =  u_ViewProjection * u_Model * vec4(a_Position, 1.0);
}


#type FRAGMENT
#version 450 core

struct Material
{
	vec3 ambient;
	vec3 diffuse;
	vec3 emission;
	vec3 specular;
	float opacity;
	bool cutoff;
	bool useTextureAsAlpha;
	float shininess;
	vec2 tiling;
};

#define NR_LIGHTS 20

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

uniform int numPointLights;
uniform	int numDirLights;
uniform	int numSpotLights;

uniform	DirectionalLight directionalLights[NR_LIGHTS];
uniform	PointLight pointLights[NR_LIGHTS];
uniform	SpotLight spotLights[NR_LIGHTS];

uniform Material material = {vec3(0.0), vec3(0.5), vec3(0.0), vec3(1.0), 1.0, false, false, 20.0, vec2(1.0)};
uniform sampler2D diffuseTexture;
uniform sampler2D emissionTexture;

in VS_OUT
{	
	vec4 v_Color;
	vec3 v_Normal;
	vec2 v_TexCoord;
	vec3 v_Position;
	vec3 v_CameraPosition;
} fs_in;

layout(location = 0) out vec4 tooncolor;
layout(location = 1) out vec4 albedocolor;
layout(location = 2) out vec4 specularcolor;
layout(location = 3) out vec4 ambientcolor;
layout(location = 4) out vec4 emissioncolor;
layout(location = 5) out vec4 normalcolor;
layout(location = 6) out vec4 positioncolor;
layout(location = 7) out vec4 texcoordcolor;

float gamma = 2.2;
float CalcDirectionalLight(DirectionalLight light, vec3 normal, vec3 fragPos, vec3 viewDirection, vec2 texCoord);
float CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDirection, vec2 texCoord);
float CalculateSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDirection, vec2 texCoord);

void main()
{
	vec3 normal = normalize(fs_in.v_Normal);
	vec3 viewDirection = normalize(fs_in.v_CameraPosition - fs_in.v_Position);
	float result = 0.0;
	vec2 texCoord = fs_in.v_TexCoord * material.tiling;
	vec3 position = fs_in.v_Position;

	for(int i = 0; i < numDirLights; i++)
	{
		result += CalcDirectionalLight(directionalLights[i], normal, position, viewDirection, texCoord);
	}

	for(int i = 0; i < numPointLights; i++)
	{
		result += CalcPointLight(pointLights[i], normal, position, viewDirection, texCoord);
	}
	
	for(int i = 0; i < numSpotLights; i++)
	{
		result += CalculateSpotLight(spotLights[i], normal, position, viewDirection, texCoord);
	}

	vec3 color = material.diffuse;// * texture(material.diffuseTexture, texCoord).rgb;
	vec3 spec = material.specular;

	if(result > .95)
	{
		color = spec ;
	}
	else if (result > .5)
	{
		color =  color;
	}
	else if(result > .25)
	{
		color = color * .5;
	}
	else
	{
		color = color * .01;
	}

	for(int i = 0; i < numDirLights; i++)
	{
		color *= directionalLights[i].color;
	}
	
	for(int i = 0; i < numPointLights; i++)
	{
		color *= pointLights[i].color;
	}
	
	for(int i = 0; i < numSpotLights; i++)
	{
		color *= spotLights[i].color;
	}

	vec4 emission = vec4(material.emission, 0.0);// * texture(material.emissionTexture, texCoord);
	vec4 ambient = vec4(material.ambient, 0.0);
	float opacity = material.useTextureAsAlpha ? texture(diffuseTexture, texCoord).a : material.opacity;
	
	if(material.cutoff == true && opacity < 0.1)
	{
		discard;
	}

	float gamma = 2.2;
	tooncolor = ambient + emission + vec4(pow(color, vec3(1.0/gamma)), opacity);
	albedocolor = vec4(pow(material.diffuse, vec3(1.0/gamma)), opacity);
	emissioncolor = vec4(emission.rgb, opacity);
	ambientcolor = vec4(ambient.rgb, opacity);
	normalcolor = vec4(normal, 1.0);
	positioncolor = vec4(position, 1.0);
	texcoordcolor = vec4(texCoord, 0.0 , 1.0);
}

float CalcDirectionalLight(DirectionalLight light, vec3 normal, vec3 fragPos, vec3 viewDirection, vec2 texCoord)
{
	vec3 lightDir = normalize(light.direction);
	vec3 viewDir = normalize(viewDirection - fragPos);
	vec3 halfwayDir = normalize(lightDir + viewDir);

	//diffuse shading
	float diff = max(dot(normal, lightDir), 0.0f);

	//spec shading
	
	float spec = pow(max(dot(normal, halfwayDir), 0.0f), material.shininess);

	return (diff + spec)  * light.brightness;
}

float CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDirection, vec2 texCoord)
{	
	vec3 lightDirection = normalize(light.position - fragPos);
	vec3 viewDir = normalize(viewDirection - fragPos);
	vec3 halfwayDir = normalize(lightDirection + viewDir);

	//diffuse shading
	float diff = max(dot(normal, lightDirection), 0.0f);

	//specular shading 
	float spec = pow(max(dot(normal, halfwayDir), 0.0), material.shininess);
	
	//for PointLight
	float distance = length(light.position - fragPos);
	float attenuation = 1.0f / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

	spec *= attenuation;
	diff *= attenuation;

	return (diff + spec) * light.brightness;
}

float CalculateSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDirection, vec2 texCoord)
{

	vec3 lightDirection = normalize(light.position - fragPos);
	vec3 viewDir = normalize(viewDirection - fragPos);
	vec3 halfwayDir = normalize(lightDirection + viewDir);

	//for spotlight
	float theta = dot(lightDirection, normalize(-light.direction));
	float epsilon = light.cutoff - light.outerCutoff;
	float intensity = clamp((theta - light.outerCutoff) / epsilon, 0.0f, 1.0f);

	//diffuse shading
	float diff = max(dot(normal, lightDirection), 0.0f);

	//specular shading	
	float spec = pow(max(dot(normal, halfwayDir), 0.0), material.shininess);

	diff *= intensity;
	spec *= intensity;

	float distance = length(light.position - fragPos);
	float attenuation = 1.0f / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

	spec *= attenuation;
	diff *= attenuation;

	return (diff + spec) *  light.brightness;
}