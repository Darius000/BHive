#type VERTEX
#version 450 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec4 a_Color;
layout(location = 2) in vec2 a_TexCoord;
layout(location = 3) in vec3 a_Normal;
layout(location = 4) in vec3 a_Tangent;
layout(location = 5) in vec3 a_BitTangent;

out vec2 v_TexCoord;

void main()
{
	gl_Position = vec4(a_Position, 1.0);
	v_TexCoord = a_TexCoord;
}

#type FRAGMENT
#version 450 core

in vec2 v_TexCoord;

uniform sampler2D scenetexture;

out vec4 FragColor;

void main()
{
	vec2 texcoord = v_TexCoord;
	vec3 color = texture(scenetexture, texcoord).rgb;
	float average = 0.2126 * color.r + 0.7152 * color.g + 0.0722 * color.b;
	FragColor = vec4(color, 1.0);
}