#type VERTEX
#version 400 core

layout(location = 0) in vec3 a_Position;


uniform mat4 u_ViewProjection;
uniform mat4 u_Model;

void main()
{
	gl_Position = u_ViewProjection * u_Model * vec4(a_Position, 1.0f);
}


#type FRAGMENT
#version 400 core

layout(location = 0) out vec4 color;


void main()
{
	color = vec4(1.0f, 0.0f, 0.0f, 1.0f);
}