#version 400 core


in vec4 vertexColor; 
in vec4 vertexPosition;
in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

out vec4 FragColor;

uniform sampler2D DiffuseTexture;
uniform sampler2D Texture2;

uniform float mixAmount;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPosition;
uniform vec3 viewPosition;

void main()
{
	vec3 ambientStrength = vec3(.1f);
	vec3 ambient = ambientStrength * lightColor;

	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(lightPosition - FragPos);

	float diffuseAmount = max(dot(normal, lightDirection), 0.0f);
	vec3 diffuse = diffuseAmount * lightColor;

	float specularStrength = .5f;
	vec3 viewDirection = normalize(viewPosition - FragPos);
	vec3 Reflection = reflect(-lightDirection, normal);

	float spec = pow(max(dot(viewDirection, Reflection), 0.0), 32);
	vec3 specular = specularStrength * spec * lightColor;

	vec3 result = (ambient + diffuse + specular) * objectColor;

	FragColor = vec4(result, 1.0f);
	//FragColor = mix(texture(DiffuseTexture, TexCoord), texture(Texture2, vec2(-TexCoord.x, TexCoord.y)), mixAmount);
};