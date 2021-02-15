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

out VS_OUT
{
	vec4 color;
	vec3 normal;
	vec3 tangent;
	vec3 bitTanget;
	vec2 texCoord;
	vec3 position;
	mat3 tbn;
	vec3 tangentPosition;
} vs_out;

		
void main()
{	
	vec3 T = normalize(vec3(u_Model * vec4(a_Tangent, 0.0)));
	vec3 N = normalize(vec3(u_Model * vec4(a_Normal, 0.0)));
	T = normalize(T - dot(T, N) * N);
	vec3 B = cross(N, T);
	mat3 TBN = transpose(mat3(T, B, N));

	gl_Position =  u_ViewProjection * u_Model * vec4(a_Position, 1.0);

	//send data to other shaders
	vs_out.tbn = TBN;
	vs_out.color = a_Color;
	vs_out.normal = normalize( vec3(u_Model * vec4(a_Normal, 0.0)));
	vs_out.tangent = T;
	vs_out.bitTanget = B;
	vs_out.texCoord = a_TexCoord;
	vs_out.position =   (u_Model * vec4(a_Position, 1.0f)).xyz;	
	vs_out.tangentPosition = TBN * vs_out.position;
}

#type GEOMETRY
#version 450 core

layout(triangles) in;
layout(line_strip, max_vertices = 6) out;

in VS_OUT
{
	vec4 color;
	vec3 normal;
	vec3 tangent;
	vec3 bitTanget;
	vec2 texCoord;
	vec3 position;
	mat3 tbn;
	vec3 tangentPosition;
} gs_in[];

out GS_OUT
{
	vec3 color;
} gs_out;

const float Magnitude = 2.0;

void GenerateLine(int index)
{
	gs_out.color = vec3(1, 0, 0);

	gl_Position = gl_in[index].gl_Position;
	EmitVertex();
	
	gl_Position = (gl_in[index].gl_Position + 
	vec4(gs_in[index].normal, 0.0) * Magnitude);	
	EmitVertex();
	EndPrimitive();

	gs_out.color = vec3(0, 1, 0);
	gl_Position = gl_in[index].gl_Position;
	EmitVertex();
	
	gl_Position = (gl_in[index].gl_Position + 
	vec4(gs_in[index].tangent, 0.0) * Magnitude);	
	EmitVertex();
	EndPrimitive();

	gs_out.color = vec3(0, 0, 1);

	gl_Position = gl_in[index].gl_Position;
	EmitVertex();
	
	gl_Position = (gl_in[index].gl_Position + 
	vec4(gs_in[index].bitTanget, 0.0) * Magnitude);	
	EmitVertex();
	EndPrimitive();
}

void main()
{
	GenerateLine(0);
}

#type FRAGMENT
#version 450 core

in GS_OUT
{
	vec3 color;
} gs_in;

out vec4 FragColor;

void main()
{
	FragColor = vec4(gs_in.color, 1.0);
}