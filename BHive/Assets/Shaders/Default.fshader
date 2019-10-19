#version 450 core

layout(location = 0) out vec4 color;

in vec4 v_Position;
in vec4 v_Color;
in vec2 v_TexCoord;

uniform vec3 u_Color;
uniform sampler2D u_Texture;

void main()
{
	//color = vec4(v_Position.xyz, 1.0);
	//color = v_Color;
	//color = vec4(v_TexCoord, 0.0, 1.0);
	//color = vec4(u_Color, 1.0);
	color = texture(u_Texture, v_TexCoord);
}