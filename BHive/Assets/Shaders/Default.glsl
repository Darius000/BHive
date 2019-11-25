#type VERTEX
#version 450 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec3 a_Color;
layout(location = 2) in vec2 a_TexCoord;

uniform mat4 u_ViewProjection;
uniform mat4 u_Model;

out vec4 v_Position;
out vec3 v_Color;
out vec2 v_TexCoord;
			
void main()
{
	v_TexCoord = a_TexCoord;
	v_Color = a_Color;
	v_Position =  vec4(a_Position, 1.0);
	gl_Position =  u_ViewProjection * u_Model * vec4(a_Position, 1.0);
}

#type FRAGMENT
#version 450 core

layout(location = 0) out vec4 color;

in vec4 v_Position;
in vec3 v_Color;
in vec2 v_TexCoord;

uniform vec4 u_Color;
uniform sampler2D u_Texture;

void main()
{
	color = texture(u_Texture, v_TexCoord) * u_Color;
}