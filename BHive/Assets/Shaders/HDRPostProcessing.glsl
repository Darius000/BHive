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

uniform float exposure;
uniform bool hdr;
uniform sampler2D hdrtexture;

out vec4 FragColor;

void main()
{
	const float gamma = 2.2;
	vec2 texcoord = v_TexCoord;
	vec3 color = texture(hdrtexture, texcoord).rgb;
	if(hdr)
	{
		vec3 mapped = vec3(1.0) - exp(-color * exposure);
		mapped = pow(mapped, vec3(1.0 / gamma));

		FragColor = vec4(mapped, 1.0);
	}
	else
	{
		vec3 result = pow(color, vec3(1.0 / gamma));
		FragColor = vec4(result, 1.0);
	}
}