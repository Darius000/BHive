#type VERTEX
#version 450 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec4 a_Color;
layout(location = 2) in vec2 a_TexCoord;
layout(location = 3) in vec3 a_Normal;

uniform mat4 u_ViewProjection;
uniform mat4 u_Model;

out vec4 v_Position;
out vec4 v_Color;
out vec2 v_TexCoord;
out vec3 v_Normal;
			
void main()
{
	v_TexCoord = a_TexCoord;
	v_Color = a_Color;
	v_Normal = a_Normal;
	v_Position =  vec4(a_Position, 1.0);
	gl_Position =  u_ViewProjection * u_Model * vec4(a_Position, 1.0);
}

#type FRAGMENT
#version 450 core

layout(location = 0) out vec4 color;

in vec4 v_Position;
in vec4 v_Color;
in vec2 v_TexCoord;
in vec3 v_Normal;

struct Material
{
	vec4 color;
	sampler2D texture;
};

uniform Material material;

void main()
{
	vec4 colorTexture = texture(material.texture, v_TexCoord);
	color =  colorTexture * material.color;
}