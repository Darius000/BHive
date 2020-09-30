#type VERTEX
#version 450 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec4 a_Color;
layout(location = 2) in vec2 a_TexCoord;
layout(location = 3) in vec3 a_Normal;
layout(location = 4) in vec3 a_Tangent;
layout(location = 5) in vec3 a_BitTangent;

uniform mat4 u_ViewProjection;
uniform mat4 u_View;
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
	OptionalTexture diffuseTexture;
	OptionalTexture specularTexture;
	OptionalTexture normalTexture;
	OptionalTexture emissionTexture;
	OptionalTexture displacementTexture;
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

struct DirectionalLight
{
	vec3 direction;
	vec3 color;
	float brightness;
};

struct PointLight
{
	vec3 position;
	vec3 color;
	float constant;
	float linear;
	float quadratic;
	float brightness;
};

struct SpotLight
{
	vec3 position;
	vec3 direction;
	vec3 color;
	float cutoff;
	float outerCutoff;
	float constant;
	float linear;
	float quadratic;
	float brightness;
};

uniform Material material;

//Lights
uniform int numPointLights;
uniform int numDirLights;
uniform int numSpotLights;

#define NR_LIGHTS 20

uniform DirectionalLight directionalLights[NR_LIGHTS];
uniform PointLight pointLights[NR_LIGHTS];
uniform SpotLight spotLights[NR_LIGHTS];

uniform vec3 CameraPosition;

in vec4 v_Color;
in vec3 v_Normal;
in vec2 v_TexCoord;
in vec3 v_Position;
in mat3 TBN;
in vec3 v_TangentPosition;

layout(location = 0) out vec4 color;

float gamma = 2.2;
vec2 ParallaxMapping(vec2 texCoords, vec3 viewDir, float scale);
vec3 CalcDirectionalLight(DirectionalLight light, vec3 normal, vec3 fragPos, vec3 viewDirection, vec2 texCoord);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDirection, vec2 texCoord);
vec3 CalculateSpotLight(SpotLight light, vec3 normal, vec3 FragPos, vec3 viewDirection, vec2 texCoord);
vec3 CalculateNormal(mat3 tbn, vec2 texcoord);

void main()
{
	vec3 v_TangentView = TBN * CameraPosition;
	vec3 viewDirection = normalize(CameraPosition - v_Position);
	vec3 fragPos = v_Position;

	if(material.displacementTexture.set)
	{
		viewDirection = normalize(v_TangentView - v_TangentPosition);
		fragPos = v_TangentPosition;
	}

	vec3 result = vec3(0.0);

	vec2 texcoord = v_TexCoord * material.tiling;
	vec2 tiledTexCoords = v_TexCoord * material.tiling;

	if(material.displacementTexture.set)
	{
		texcoord = ParallaxMapping(texcoord, viewDirection, material.heightScale);
		if(material.discardEdges && (texcoord.x > 1.0 || texcoord.y > 1.0 || texcoord.x < 0.0 || texcoord.y < 0.0))
			discard;
	}

	vec3 normal = v_Normal;
	if(material.normalTexture.set)
		normal = CalculateNormal(TBN, texcoord);

	if(material.doublesided)
	{
		if(gl_FrontFacing == false)
		{
			normal = -normal;
		}
	}

	for(int i = 0; i < numDirLights; i++)
	{
		result += CalcDirectionalLight(directionalLights[i], normal, fragPos, viewDirection, texcoord);
	}

	for(int i = 0; i < numPointLights; i++)
	{
		result += CalcPointLight(pointLights[i], normal, fragPos, viewDirection, texcoord);
	}
	
	for(int i = 0; i < numSpotLights; i++)
	{
		result += CalculateSpotLight(spotLights[i], normal, fragPos, viewDirection, texcoord);
	}

	vec4 emission = texture(material.emissionTexture.texture, texcoord) * vec4(material.emission, 0.0);
	vec4 ambient = vec4(material.ambient, 0.0);
	float alpha = material.useTextureAsAlpha ? texture(material.diffuseTexture.texture, texcoord).a : material.opacity;

	if(material.cutoff == true && alpha < 0.1)
	{
		discard;
	}

	float gamma = 2.2;
	
	color = ambient + emission + vec4(pow(result, vec3(1.0/gamma)), alpha);
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
	float currentDepthMapValue = texture(material.displacementTexture.texture, texCoords).r;
	
	while(currentLayerDepth < currentDepthMapValue)
	{
		currentTexCoords -= deltaTexCoords;
		currentDepthMapValue = texture(material.displacementTexture.texture, currentTexCoords).r;
		currentLayerDepth += layerDepth;
	}

	vec2 prevTexCoords = currentTexCoords + deltaTexCoords;

	float afterDepth = currentDepthMapValue - currentLayerDepth;
	float beforeDepth = texture(material.displacementTexture.texture, prevTexCoords).r - currentLayerDepth + layerDepth;

	float weight = afterDepth/(afterDepth - beforeDepth);
	vec2 finalTexCoords = prevTexCoords * weight + currentTexCoords * (1.0 - weight) ;

	return finalTexCoords;
}

vec3 CalculateNormal(mat3 tbn, vec2 texcoord)
{
	vec3 normalmap = texture(material.normalTexture.texture, texcoord).rgb ;
	return 2.0 * normalmap - 1.0;
}

vec3 CalcDirectionalLight(DirectionalLight light, vec3 normal, vec3 fragPos, vec3 viewDirection, vec2 texCoord)
{
	vec3 lightdir = material.normalTexture.set ? normalize(TBN * light.direction)  : normalize(light.direction);
	vec3 viewDir = normalize(viewDirection - fragPos);
	vec3 halfwayDir = normalize(lightdir + viewDir);

	//diffuse shading
	float diff = max(dot(normal, lightdir), 0.0f);

	//spec shading
	
	float spec = pow(max(dot(normal, halfwayDir), 0.0f),  max(1.0, material.shininess));

	
	//combine
	vec3 diffuse = diff * pow(texture(material.diffuseTexture.texture, texCoord).rgb, vec3(gamma)) * material.diffuse;
	vec3 specular = spec * vec3(texture(material.specularTexture.texture, texCoord)) * material.specular;
	return ((diffuse + specular) * light.color) * max(0.0, light.brightness);
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDirection, vec2 texCoord)
{	
	vec3 lightpos = material.normalTexture.set ? TBN * light.position : light.position;
	vec3 lightDirection = normalize(lightpos - fragPos);
	vec3 viewDir = normalize(viewDirection - fragPos);
	vec3 halfwayDir = normalize(lightDirection + viewDir);

	//diffuse shading
	float diff = max(dot(normal, lightDirection), 0.0f);

	//specular shading 
	float spec = pow(max(dot(normal, halfwayDir), 0.0),  max(1.0, material.shininess));
	
	//for PointLight
	float distance = length(lightpos - fragPos);
	float attenuation = 1.0f / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

	vec3 diffuse =	diff *	pow(texture(material.diffuseTexture.texture, texCoord).rgb, vec3(gamma)) * material.diffuse;
	vec3 specular = spec *	vec3(texture(material.specularTexture.texture, texCoord)) * material.specular ;


	specular *= attenuation;
	diffuse *= attenuation;

	return ((diffuse + specular) * light.color) * max(0.0, light.brightness);
}

vec3 CalculateSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDirection, vec2 texCoord)
{
	vec3 lightdir = material.normalTexture.set ? TBN * light.direction : light.direction;
	vec3 lightpos = material.normalTexture.set ? TBN * light.position : light.position;
	vec3 lightDirection = normalize(lightpos - fragPos);
	vec3 viewDir = normalize(viewDirection - fragPos);
	vec3 halfwayDir = normalize(lightDirection + viewDir);

	//for spotlight
	float theta = dot(lightDirection, normalize(-lightdir));
	float epsilon = light.cutoff - light.outerCutoff;
	float intensity = clamp((theta - light.outerCutoff) / epsilon, 0.0f, 1.0f);

	//diffuse shading
	float diff = max(dot(normal, lightDirection), 0.0f);

	//specular shading	
	float spec = pow(max(dot(normal, halfwayDir), 0.0), max(1.0, material.shininess));

	vec3 diffuse = diff *  pow(texture(material.diffuseTexture.texture, texCoord).rgb, vec3(gamma)) * material.diffuse;
	vec3 specular = spec * vec3(texture(material.specularTexture.texture, texCoord)) * material.specular;
	
	diffuse *= intensity;
	specular *= intensity;

	float distance = length(lightpos - fragPos);
	float attenuation = 1.0f / (light.constant + light.linear * distance + light.quadratic * (distance * distance));


	specular *= attenuation;
	diffuse *= attenuation;

	return ((diffuse + specular) * light.color) * max(0.0, light.brightness);
}