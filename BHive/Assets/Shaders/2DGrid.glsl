#type VERTEX
#version 450 core

layout(location = 0) in vec3 a_Position;
layout(location = 2) in vec2 a_TexCoord;

layout(std140) uniform Matrices
{
	mat4 u_ViewProjection;
	mat4 u_Projection;
	vec3 u_CameraPosition;
};

uniform mat4 u_Model;

out highp vec2 v_TexCoord;

void main()
{

	gl_Position = u_ViewProjection  * vec4(a_Position, 1.0);
	v_TexCoord = a_TexCoord;
}

#type FRAGMENT
#version 450 core

in highp vec2 v_TexCoord;

struct Material
{
	float scale;
	vec4 lineColor;
};

uniform Material material;

layout(location = 3) out vec4 color;

void main()
{
	vec2 grid_uv = v_TexCoord * material.scale;
	float x = cos(grid_uv.x);
	float y = cos(grid_uv.y);
	if(x < 0.95f && y < .95f)
	{
		color = vec4(0.0, 0.0, 0.0, 0.0);
	}
	else
	{
		color = material.lineColor;
	}
}
