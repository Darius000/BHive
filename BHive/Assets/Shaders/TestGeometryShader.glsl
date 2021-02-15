#type VERTEX
#version 450 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec4 a_Color;
layout(location = 2) in vec2 a_TexCoord;
layout(location = 3) in vec3 a_Normal;
layout(location = 4) in vec3 a_Tangent;
layout(location = 5) in vec3 a_BitTangent;

layout(std140) uniform Matrices
{
	mat4 u_ViewProjection;
	mat4 u_Projection;
	vec3 u_CameraPosition;
};

uniform mat4 u_Model;

out VS_OUT{
	vec3 color;
} vs_out;

void main()
{
	gl_Position = u_ViewProjection * u_Model * vec4(a_Position, 1.0);
	vs_out.color = vec3(a_Color);
}

#type GEOMETRY
#version 450 core

layout(triangles) in;
layout(triangle_strip, max_vertices = 5) out;

in VS_OUT
{
	vec3 color;
} gs_in[];

out vec3 fColor;

void BuildHouse(vec4 position)
{
	fColor = gs_in[0].color;
	gl_Position = position + vec4(-.2, -.2, 0, 0);
	EmitVertex();

	gl_Position = position + vec4(.2, -.2, 0, 0);
	EmitVertex();

	gl_Position = position + vec4(-.2, .2, 0, 0);
	EmitVertex();

	gl_Position = position + vec4(.2, .2, 0, 0);
	EmitVertex();

	gl_Position = position + vec4(0, .4, 0, 0);
	fColor = vec3(1.0, 1.0, 1.0);
	EmitVertex();
	EndPrimitive();
}

void main()
{
	BuildHouse(gl_in[0].gl_Position);
}

#type FRAGMENT
#version 450 core

out vec4 FragColor;

in vec3 fColor;

void main()
{
	FragColor = vec4(fColor, 1.0);
}