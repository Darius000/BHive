#version 400 core

uniform vec3 boundsColor;

out vec4 fragColor;

void main()
{
	fragColor = vec4(boundsColor, 1.0f);
}