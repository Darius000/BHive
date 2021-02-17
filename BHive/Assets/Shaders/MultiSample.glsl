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

uniform sampler2D scene;
uniform int numSamples;

layout(location = 0) out vec4 color;

void main()
{
	vec2 tex_offset = 1.0 / textureSize(scene, 0);
	vec3 sceneColor = texture(scene, v_TexCoord).rgb;
	vec3 sampledColor = sceneColor;


	for(int i = 0; i < numSamples; i ++)
	{
		sampledColor += texture(scene, v_TexCoord + vec2(tex_offset.x * i, 0)).rgb;
		sampledColor += texture(scene, v_TexCoord - vec2(tex_offset.x * i, 0)).rgb; 
		sampledColor += texture(scene, v_TexCoord + vec2(0, tex_offset.y * 1)).rgb;
		sampledColor += texture(scene, v_TexCoord - vec2(0, tex_offset.y * 1)).rgb;
	};
 
	color = vec4(sceneColor, 1.0);
}