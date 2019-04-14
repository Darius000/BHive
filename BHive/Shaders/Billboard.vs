#version 400 core

uniform mat4 PVM;

layout(location = 0) in vec3 Position;
layout(location = 1) in vec2 TexCoord;

out vec2 TexCoords;

void main(void)
{
	gl_Position = PVM * vec4(Position, 1.0);
	TexCoords = TexCoord;
}