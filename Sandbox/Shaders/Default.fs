#version 400 core


out vec4 FragColor;
in vec4 vertexColor;
in vec4 vertexPosition;
//uniform vec4 ourColor;

void main()
{
	//FragColor = vertexColor;
	FragColor = vertexPosition;
};