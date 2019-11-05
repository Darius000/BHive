#type VERTEX
#version 450 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec3 a_Color;
layout(location = 2) in vec2 a_TexCoord;
layout(location = 3) in vec3 a_Normal;

uniform mat4 u_ViewProjection;
uniform mat4 u_Model;

out vec3 v_Color;
out vec3 v_Normal;
out vec2 v_TexCoord;
out vec3 v_Position;
			
void main()
{	
	v_Color = a_Color;
	v_Normal = a_Normal;
	v_TexCoord = a_TexCoord;
	v_Position =  vec3(u_Model * vec4(a_Position, 1.0));
	gl_Position =  u_ViewProjection * u_Model * vec4(a_Position, 1.0);
}

#type FRAGMENT
#version 400 core

in vec3 v_Color;
in vec3 v_Normal;
in vec2 v_TexCoord;
in vec3 v_Position;

layout(location = 0) out vec4 color;

struct Material
{
	sampler2D diffuse;
	vec3 color;
	float transparency;
};

struct DirectionalLight
{
	vec3 direction;
	vec3 color;
	float brightness;
};

uniform Material material;
uniform DirectionalLight directionalLight;

vec4 CalculateLambertDirLight(vec3 normal,  DirectionalLight light, vec3 pos, Material mat, vec2 texcoord)
{
	vec3 norm = normalize(normal);
	vec3 lightDir = normalize(light.direction - pos);

	float diff = max(dot(normal, light.direction), 0.0);
	vec3 diffuse = diff * light.color * light.brightness * mat.color ;
	return vec4(diffuse, mat.transparency) * texture(mat.diffuse, texcoord);
}

void main()
{
	color = CalculateLambertDirLight(v_Normal, directionalLight, v_Position, material, v_TexCoord);
}