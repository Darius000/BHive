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
	mat4 u_View;
};

uniform mat4 u_Model;

out vec4 v_Color;
out vec3 v_Normal;
out vec2 v_TexCoord;
out vec3 v_Position;
out mat3 TBN;
out vec3 v_TangentPosition;
		
void main()
{	
	v_Color = a_Color;

	vec3 T = normalize(vec3(u_Model * vec4(a_Tangent, 0.0)));
	vec3 N = normalize(vec3(u_Model * vec4(a_Normal, 0.0)));
	T = normalize(T - dot(T, N) * N);
	vec3 B = cross(N, T);
	TBN = transpose(mat3(T, B, N));

	v_Normal = normalize( vec3(u_Model * vec4(a_Normal, 0.0)));
	v_TexCoord = a_TexCoord;
	v_Position =   (u_Model * vec4(a_Position, 1.0f)).xyz;
	gl_Position =  u_ViewProjection * u_Model * vec4(a_Position, 1.0);
	v_TangentPosition = TBN * v_Position;
	
}


#type FRAGMENT
#version 450 core

struct OptionalTexture
{
	sampler2D texture;
	bool set;
};

struct Material
{
	vec3 ambient;
	vec3 diffuse;
	vec3 emission;
	vec3 specular;
	float opacity;
	bool cutoff;
	bool useTextureAsAlpha;
	bool doublesided;
	float shininess;
	float heightScale;
	bool discardEdges;
	vec2 tiling;
};

struct Textures
{
	OptionalTexture diffuseTexture;
	OptionalTexture specularTexture;
	OptionalTexture normalTexture;
	OptionalTexture emissionTexture;
	OptionalTexture displacementTexture;
	OptionalTexture AOTexture;
};

uniform Textures textures;

uniform Material material = {
	{0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f},
	1.0f,
	false,
	false,
	false,
	20.0f,
	0.0f,
	false,
	{1.0f, 1.0f}};
uniform vec3 CameraPosition;

in vec4 v_Color;
in vec3 v_Normal;
in vec2 v_TexCoord;
in vec3 v_Position;
in mat3 TBN;
in vec3 v_TangentPosition;

layout(location = 1) out vec4 albedocolor;
layout(location = 2) out vec4 specularcolor;
layout(location = 3) out vec4 ambientcolor;
layout(location = 4) out vec4 emissioncolor;
layout(location = 5) out vec4 normalcolor;
layout(location = 6) out vec4 positioncolor;
layout(location = 7) out vec4 texcoordcolor;

float gamma = 2.2;
vec2 ParallaxMapping(vec2 texCoords, vec3 viewDir, float scale);
vec3 CalculateNormal(mat3 tbn, vec2 texcoord);

void main()
{
	vec3 v_TangentView = TBN * CameraPosition;
	vec3 FragPos = v_Position;
	vec3 viewDirection = vec3(1.0);
	if(textures.displacementTexture.set)
	{
		viewDirection = normalize(v_TangentView - v_TangentPosition);
		FragPos = v_TangentPosition;
	}

	vec2 texcoord = v_TexCoord * material.tiling;

	if(textures.displacementTexture.set)
	{
		texcoord = ParallaxMapping(texcoord, viewDirection, material.heightScale);
		if(material.discardEdges && (texcoord.x > 1.0 || texcoord.y > 1.0 || texcoord.x < 0.0 || texcoord.y < 0.0))
			discard;
	}

	vec3 normal = v_Normal;
	if(textures.normalTexture.set)
		normal = CalculateNormal(TBN, texcoord);

	if(material.doublesided)
	{
		if(gl_FrontFacing == false)
		{
			normal = -normal;
		}
	}

	vec4 emission = vec4(material.emission, 0.0);

	if(textures.emissionTexture.set)
	{
		emission *= texture(textures.emissionTexture.texture, texcoord);
	}

	float opacity = material.useTextureAsAlpha ? texture(textures.diffuseTexture.texture, texcoord).a : material.opacity;

	if(material.cutoff == true && opacity < 0.1)
	{
		discard;
	}

	albedocolor = vec4(material.diffuse, opacity);
	if(textures.diffuseTexture.set)
		albedocolor.rgb *= texture(textures.diffuseTexture.texture, texcoord).rgb;

	specularcolor = vec4(material.specular, 1.0);
	if(textures.specularTexture.set)
		specularcolor.rgb *= texture(textures.specularTexture.texture, texcoord).rgb;

	emissioncolor = vec4(emission.rgb, opacity);

	//AO
	float AO = textures.AOTexture.set ? texture(textures.AOTexture.texture, texcoord).r : 1.0f;

	ambientcolor = vec4(vec3(AO), 1.0);

	normalcolor = vec4(normal, 1.0);
	positioncolor = vec4(FragPos, 1.0);
	texcoordcolor = vec4(texcoord, 0.0 , 1.0);
}

vec2 ParallaxMapping(vec2 texCoords, vec3 viewDir, float scale)
{
	const float minLayers = 8.0;
	const float maxLayers = 32.0;

	//depth layers
	const float numLayers = mix(maxLayers, minLayers, max(dot(vec3(0.0,0.0,1.0), viewDir), 0.0));

	float layerDepth = 1.0 / numLayers;

	float currentLayerDepth = 0.0;

	vec2 p = viewDir.xy * scale;
	vec2 deltaTexCoords = p / numLayers;

	vec2 currentTexCoords = texCoords;
	float currentDepthMapValue = texture(textures.displacementTexture.texture, texCoords).r;
	
	while(currentLayerDepth < currentDepthMapValue)
	{
		currentTexCoords -= deltaTexCoords;
		currentDepthMapValue = texture(textures.displacementTexture.texture, currentTexCoords).r;
		currentLayerDepth += layerDepth;
	}

	vec2 prevTexCoords = currentTexCoords + deltaTexCoords;

	float afterDepth = currentDepthMapValue - currentLayerDepth;
	float beforeDepth = texture(textures.displacementTexture.texture, prevTexCoords).r - currentLayerDepth + layerDepth;

	float weight = afterDepth/(afterDepth - beforeDepth);
	vec2 finalTexCoords = prevTexCoords * weight + currentTexCoords * (1.0 - weight) ;

	return finalTexCoords;
}

vec3 CalculateNormal(mat3 tbn, vec2 texcoord)
{
	vec3 normalmap = texture(textures.normalTexture.texture, texcoord).rgb ;
	return 2.0 * normalmap - 1.0;
}
