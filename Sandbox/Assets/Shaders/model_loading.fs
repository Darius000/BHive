#version 400 core

out vec4 FragColor;

in vec3 VertexColor; 
in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

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

#define NR_POINT_LIGHTS 4
uniform PointLight pointLights[NR_POINT_LIGHTS];

uniform sampler2D texture_diffuse1;
//uniform sampler2D texture_diffuse2;
//uniform sampler2D texture_diffuse3;
uniform sampler2D texture_specular1;
//uniform sampler2D texture_specular2;
//uniform sampler2D texture_specular3;
//uniform sampler2D texture_emission1;
//uniform sampler2D texture_emission2;
//uniform sampler2D texture_emission3;

uniform vec3 viewPosition;

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDirection);

void main()
{
	vec3 normal = normalize(Normal);
	vec3 viewDirection = normalize(viewPosition - FragPos);

	vec3 result;

	for(int i = 0; i < NR_POINT_LIGHTS; i++)
	{
		result += CalcPointLight(pointLights[i], normal, FragPos, viewDirection);
	}

	FragColor = vec4(result, 1.0f);
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDirection)
{	
	vec3 lightDirection = normalize(light.position - FragPos);

	//diffuse shading
	float diff = max(dot(normal, lightDirection), 0.0f);

	//specular shading 
	vec3 Reflection = reflect(-lightDirection, normal);
	float spec = pow(max(dot(viewDirection, Reflection), 0.0), 32);
	
	//for PointLight
	float distance = length(light.position - FragPos);
	float attenuation = 1.0f / (light.constant + (light.linear * distance) + (light.quadratic * (distance * distance)));

	vec3 ambient =  light.ambient	*	vec3(texture(texture_diffuse1, TexCoord));
	vec3 diffuse =	light.diffuse	*	diff *	vec3(texture(texture_diffuse1, TexCoord));
	vec3 specular = light.specular	*	spec *	vec3(texture(texture_specular1, TexCoord));

	ambient *= attenuation;
	specular *= attenuation;
	diffuse *= attenuation;

	return ambient + diffuse + specular;
}