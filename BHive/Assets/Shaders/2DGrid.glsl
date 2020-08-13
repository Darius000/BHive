#type VERTEX
#version 450 core

layout(location = 0) in vec3 a_Position;
layout(location = 2) in vec2 a_TexCoord;

uniform mat4 u_ViewProjection;

out highp vec2 v_TexCoord;

void main()
{

	gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
	v_TexCoord = a_TexCoord;
}

#type FRAGMENT
#version 450 core

in highp vec2 v_TexCoord;
uniform float scale;
uniform float resolution;
uniform vec4 lineColor;
uniform vec4 backgroundColor;

out vec4 color;

float grid(vec2 steps, float res)
{
	vec2 grid = fract(steps * res);
	return (step(res, grid.x) * step(res, grid.y));
}

void main()
{
	vec2 grid_uv = v_TexCoord * scale;
	float x = grid(grid_uv, resolution);
	if(x > 0.0f)
	{
		color = backgroundColor;
	}
	else
	{
		color = lineColor;
	}
}
