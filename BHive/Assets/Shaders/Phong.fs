#version 400 core

struct Material
{

	sampler2D diffuse;
	sampler2D specular;
	sampler2D emission;

	float shininess;
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

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
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

uniform DirectionalLight dirLight;
#define NR_POINT_LIGHTS 4
uniform PointLight pointLights[NR_POINT_LIGHTS];
uniform SpotLight spotLight;

uniform float time;
uniform vec3 viewPosition;

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

out vec4 FragColor;

//calculate directional light
vec3 CalcDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDirection);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDirection);
vec3 CalculateSpotLight(SpotLight light, vec3 normal, vec3 FragPos, vec3 viewDirection);

void main()
{
	vec3 normal = normalize(Normal);
	vec3 viewDirection = normalize(viewPosition - FragPos);

	vec3 result = CalcDirectionalLight(dirLight, normal, viewDirection);

	for(int i = 0; i < NR_POINT_LIGHTS; i++)
	{
		result += CalcPointLight(pointLights[i], normal, FragPos, viewDirection);
	}

	//add spotlight
	result += CalculateSpotLight(spotLight, Normal, FragPos, viewDirection);

	FragColor = vec4(result, 1.0f);
}

vec3 CalcDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDirection)
{
	vec3 lightDir = normalize(-light.direction);

	//diffuse shading
	float diff = max(dot(normal, lightDir), 0.0f);

	//spec shading
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(reflectDir, viewDirection), 0.0f), material.shininess);

	//combine
	vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoord));
	vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoord));
	vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoord));
	return ambient + diffuse + specular;
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDirection)
{	
	vec3 lightDirection = normalize(light.position - FragPos);

	//diffuse shading
	float diff = max(dot(normal, lightDirection), 0.0f);

	//specular shading 
	vec3 Reflection = reflect(-lightDirection, normal);
	float spec = pow(max(dot(viewDirection, Reflection), 0.0), material.shininess);
	
	//for PointLight
	float distance = length(light.position - FragPos);
	float attenuation = 1.0f / (light.constant + (light.linear * distance) + (light.quadratic * (distance * distance)));

	vec3 ambient =  light.ambient	*	vec3(texture(material.diffuse, TexCoord));
	vec3 diffuse =	light.diffuse	*	diff *	vec3(texture(material.diffuse, TexCoord));
	vec3 specular = light.specular	*	spec *	vec3(texture(material.specular, TexCoord));

	ambient *= attenuation;
	specular *= attenuation;
	diffuse *= attenuation;

	return ambient + diffuse + specular;
}

vec3 CalculateSpotLight(SpotLight light, vec3 normal, vec3 FragPos, vec3 viewDirection)
{

	vec3 lightDirection = normalize(light.position - FragPos);

	//for spotlight
	float theta = dot(lightDirection, normalize(-light.direction));
	float epsilon = light.cutoff - light.outerCutoff;
	float intensity = clamp((theta - light.outerCutoff) / epsilon, 0.0f, 1.0f);

	//diffuse shading
	float diff = max(dot(normal, lightDirection), 0.0f);

	//specular shading	
	vec3 Reflection = reflect(-lightDirection, normal);
	float spec = pow(max(dot(viewDirection, Reflection), 0.0), material.shininess);

	vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoord));
	vec3 diffuse = diff * light.diffuse * vec3(texture(material.diffuse, TexCoord));
	vec3 specular = spec * light.specular * vec3(texture(material.specular, TexCoord));

	diffuse *= intensity;
	specular *= intensity;

	return ambient + diffuse + specular;
}