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

layout(std140, binding = 2) uniform Time
{
	float time;
};

uniform mat4 u_Model;

out VS_OUT{
	float time;
} vs_out;

void main()
{
	gl_Position = u_ViewProjection * u_Model * vec4(a_Position, 1.0);
	vs_out.time = time;
}

#type GEOMETRY
#version 450 core

layout(triangles) in;
layout(triangle_strip, max_vertices = 5) out;

in VS_OUT
{
	float time;
} gs_in[];

out float time;

vec3 GetNormal()
{
	vec3 a = vec3(gl_in[0].gl_Position) -  vec3(gl_in[1].gl_Position);
	vec3 b = vec3(gl_in[2].gl_Position) -  vec3(gl_in[1].gl_Position);
	return normalize(cross(a, b));
}

vec4 explode(vec4 position, vec3 normal)
{
	float magnitude = 2.0f;
	vec3 direction = normal * ((sin(gs_in[0].time) + 1.0) / 2.0) * magnitude;
	return position + vec4(direction, 0.0);
}

void main()
{
	vec3 normal = GetNormal();

	gl_Position = explode(gl_in[0].gl_Position, normal);
	EmitVertex();

	gl_Position = explode(gl_in[1].gl_Position, normal);
	EmitVertex();

	gl_Position = explode(gl_in[2].gl_Position, normal);
	EmitVertex();

	EndPrimitive();

	time = gs_in[0].time;
}

#type FRAGMENT
#version 450 core


in float time;

out vec4 FragColor;

void main()
{
	FragColor = vec4(1.0 * sin(10 * time) + 1.0, 0.0, 0.0,  1.0) ;
}