#type VERTEX
#version 450 core

layout(location = 0) in vec3 a_Position;
layout(location = 2) in vec2 a_TexCoord;


out vec2 v_TexCoord;

void main()
{
	gl_Position = vec4(a_Position, 1.0);
	v_TexCoord = a_TexCoord;
}

#type FRAGMENT
#version 450 core

in vec2 v_TexCoord;

layout(location = 6) uniform sampler2D albedocolor;
layout(location = 7) uniform sampler2D specularcolor;
layout(location = 8) uniform sampler2D ambientcolor;
layout(location = 9) uniform sampler2D emissioncolor;
layout(location = 10) uniform sampler2D normalcolor;
layout(location = 11) uniform sampler2D positioncolor;
layout(location = 12) uniform sampler2D bloomtexture;

//HDR
uniform float exposure;
uniform bool hdr;
uniform bool bloom;

//Lights
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

struct LightColor
{
	float diffuse;
	float specular;
	vec3 color;
};

uniform int numPointLights;
uniform int numDirLights;
uniform int numSpotLights;

#define NR_LIGHTS 20

uniform DirectionalLight directionalLights[NR_LIGHTS];
uniform PointLight pointLights[NR_LIGHTS];
uniform SpotLight spotLights[NR_LIGHTS];

uniform vec3 CameraPosition;

layout(location = 0) out vec4 FragColor;

vec3 ToneMap(vec3 color)
{
	const float gamma = 2.2;
	vec3 hdrcolor = color;

	vec3 mapped = vec3(1.0) - exp(-color * exposure);

	mapped = pow(mapped, vec3(1.0 / gamma));

	return mapped;
}

LightColor CalcDirectionalLight(DirectionalLight light, float shininess,vec3 normal, vec3 fragPos, vec3 viewDirection, vec2 texCoord);
LightColor CalcPointLight(PointLight light, float shininess, vec3 normal, vec3 fragPos, vec3 viewDirection, vec2 texCoord);
LightColor CalculateSpotLight(SpotLight light, float shininess, vec3 normal, vec3 FragPos, vec3 viewDirection, vec2 texCoord);
LightColor CalculateLights(float shininess,vec3 normal, vec3 fragPos, vec3 viewDirection, vec2 texCoord);

void main()
{
	vec2 texcoord = v_TexCoord;
	vec3 result = vec3(0.0);
	vec3 normal = texture(normalcolor, texcoord).rgb;
	vec3 albedo = texture(albedocolor, texcoord).rgb;
	vec3 fragPos = texture(positioncolor, texcoord).rgb;
	vec3 specular = texture(specularcolor, texcoord).rgb;
	vec3 ambient = texture(ambientcolor, texcoord).rgb;
	vec3 emission = texture(emissioncolor, texcoord).rgb;
	float opacity = texture(albedocolor, texcoord).a;
	float shininess = texture(specularcolor, texcoord).a * 200.0f;
	vec3 viewDirection = normalize(CameraPosition - fragPos);

	LightColor L = CalculateLights(shininess, normal, fragPos, viewDirection, texcoord);
	result = (L.diffuse  * ambient * albedo + L.specular  * specular ) * L.color  + emission  ;

	vec3 bloomcolor = texture(bloomtexture, texcoord).rgb;
	if(bloom == true)
		result += bloomcolor;
	vec3 finalcolor = hdr ? ToneMap(result) : result;
	FragColor = vec4(finalcolor, opacity);
}

LightColor CalculateLights( float shininess,vec3 normal, vec3 fragPos, vec3 viewDirection, vec2 texCoord)
{
	LightColor final;
	for(int i = 0; i < numDirLights; i++)
	{
		LightColor L = CalcDirectionalLight(directionalLights[i], shininess, normal, fragPos, viewDirection, texCoord);
		final.diffuse += L.diffuse;
		final.specular += L.specular;
		final.color += L.color;
	}

	for(int i = 0; i < numPointLights; i++)
	{
		LightColor L = CalcPointLight(pointLights[i], shininess, normal, fragPos, viewDirection, texCoord);
		final.diffuse += L.diffuse;
		final.specular += L.specular;
		final.color += L.color;
	}
	
	for(int i = 0; i < numSpotLights; i++)
	{
		LightColor L = CalculateSpotLight(spotLights[i], shininess, normal, fragPos, viewDirection, texCoord);
		final.diffuse += L.diffuse;
		final.specular += L.specular;
		final.color += L.color;
	}

	return final;
}

LightColor CalcDirectionalLight(DirectionalLight light, float shininess, vec3 normal, vec3 fragPos, vec3 viewDirection, vec2 texCoord)
{
	vec3 lightdir = normalize(light.direction);
	vec3 viewDir = normalize(viewDirection - fragPos);
	vec3 halfwayDir = normalize(lightdir + viewDir);

	//diffuse shading
	float diff = max(dot(normal, lightdir), 0.0f);

	//spec shading	
	float spec = pow(max(dot(normal, halfwayDir), 0.0f),  max(1.0, shininess));

	LightColor L = {diff * max(0.0, light.brightness), spec, light.color * light.brightness};
	return L;
}

LightColor CalcPointLight(PointLight light, float shininess, vec3 normal, vec3 fragPos, vec3 viewDirection, vec2 texCoord)
{	
	vec3 lightpos = light.position;
	vec3 lightDirection = normalize(lightpos - fragPos);
	vec3 viewDir = normalize(viewDirection - fragPos);
	vec3 halfwayDir = normalize(lightDirection + viewDir);

	//diffuse shading
	float diff = max(dot(normal, lightDirection), 0.0f) ;

	//specular shading 
	float spec = pow(max(dot(normal, halfwayDir), 0.0),  max(1.0, shininess)) ;
	
	//for PointLight
	float distance = length(lightpos - fragPos);
	float attenuation = 1.0f / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

	LightColor L = {diff * max(0.0, light.brightness), spec, light.color * light.brightness};
	return L;
}

LightColor CalculateSpotLight(SpotLight light, float shininess, vec3 normal, vec3 fragPos, vec3 viewDirection, vec2 texCoord)
{
	vec3 lightdir = light.direction;
	vec3 lightpos = light.position;
	vec3 lightDirection = normalize(lightpos - fragPos);
	vec3 viewDir = normalize(viewDirection - fragPos);
	vec3 halfwayDir = normalize(lightDirection + viewDir);

	//for spotlight
	float theta = dot(lightDirection, normalize(-lightdir));
	float epsilon = light.cutoff - light.outerCutoff;
	float intensity = clamp((theta - light.outerCutoff) / epsilon, 0.0f, 1.0f);

	//diffuse shading
	float diff = max(dot(normal, lightDirection), 0.0f);

	//specular shading	
	float spec = pow(max(dot(normal, halfwayDir), 0.0), max(1.0, shininess));

	diff *= intensity;
	spec *= intensity;

	float distance = length(lightpos - fragPos);
	float attenuation = 1.0f / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

	diff *= attenuation;
	spec *= attenuation;

	LightColor L = {diff * max(0.0, light.brightness), spec , light.color * light.brightness};
	return L;
}