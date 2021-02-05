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

uniform sampler2D image;

uniform bool horizontal;
float weight[5] = float[](0.2270270270, 0.1945945946, 0.1216216216, 0.0540540541, 0.0162162162);

out vec4 color;

void main()
{
	vec2 tex_offset = 1.0 / textureSize(image, 0);
	vec3 result = texture(image, v_TexCoord).rgb * weight[0];

	if(horizontal)
	{
		for(int i = 1; i < 5; ++i)
		{
			result += texture(image, v_TexCoord + vec2(tex_offset.x * i, 0.0)).rgb * weight[i];
			result += texture(image, v_TexCoord - vec2(tex_offset.x * i, 0.0)).rgb * weight[i];
		}
	}
	else
	{
		for(int i = 1; i < 5; ++i)
		{
			result += texture(image, v_TexCoord + vec2(0.0, tex_offset.y * i)).rgb * weight[i];
			result += texture(image, v_TexCoord - vec2(0.0, tex_offset.y * i)).rgb * weight[i];
		}
	}

	color = vec4(result, 1.0);
}
