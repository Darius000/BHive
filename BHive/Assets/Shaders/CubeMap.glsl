#type VERTEX
#version 450 core

layout(location = 0) in vec3 a_Position;

layout(std140) uniform Matrices
{
	mat4 u_ViewProjection;
	mat4 u_Projection;
	vec3 u_CameraPosition;
};

layout(std140) uniform CubeMatrices
{
	mat4 u_CubeProjection;
};

uniform mat4 u_Model;


out vec3 v_TexCoord;
		
void main()
{	
	v_TexCoord = a_Position;
	vec4 pos = u_CubeProjection * u_Model * vec4(a_Position, 1.0);
	gl_Position =  pos;
}


#type FRAGMENT
#version 450 core

layout(location = 1) out vec4 albedocolor;
layout(location = 2) out vec4 specularcolor;
layout(location = 3) out vec4 ambientcolor;
layout(location = 4) out vec4 emissioncolor;
layout(location = 5) out vec4 normalcolor;
layout(location = 6) out vec4 positioncolor;
layout(location = 7) out vec4 texcoordcolor;

in vec3 v_TexCoord;


struct Textures
{
	samplerCube CubeMap;
};

uniform Textures textures;

void main()
{
	vec4 color = texture(textures.CubeMap, v_TexCoord);
	albedocolor		= color;
	emissioncolor	= color;
	specularcolor	= vec4(vec3(0.0), 1.0);
	ambientcolor	= vec4(vec3(0.0), 1.0);
	normalcolor		= vec4(vec3(0.0), 1.0);
	positioncolor	= vec4(vec3(0.0), 1.0);
	texcoordcolor	= vec4(vec3(0.0), 1.0);
}