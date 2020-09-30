#include "BHivePCH.h"
#include "Material.h"
#include "Managers/AssetManagers.h"

namespace BHive
{

	Material::Material() :m_Shader(nullptr)
	{

	}

	void Material::Render()
	{
		if (m_Shader)
		{
			m_Shader->Bind();

			for (const auto& uniform : GetShaderUniforms())
			{				
				m_Shader->SetUniform(uniform);
			}
		}
	}

	DefaultMaterial::DefaultMaterial()
	{
		m_Shader = AssetManager::Get<Shader>("Default");
		m_ShaderUniforms.Add({
			UNIFORM(material.ambient, Ambient, DefaultMaterial, m_Properties.m_AmbientColor, Color3),
			UNIFORM(material.diffuse, Diffuse, DefaultMaterial, m_Properties.m_DiffuseColor, Color3),
			UNIFORM(material.opacity, Opacity, DefaultMaterial, m_Properties.m_Opacity, Float),
			UNIFORM(material.tiling, Tiling, DefaultMaterial, m_Properties.m_TextureTiling, Vec2)
		});
	}

	LambertMaterial::LambertMaterial()
		:DefaultMaterial()
	{
		m_Shader = AssetManager::Get<Shader>("Lambert");
	}

	PhongMaterial::PhongMaterial()
	{
		m_Shader = AssetManager::Get<Shader>("BlinnPhong");

		m_ShaderUniforms.Add({
			UNIFORM(material.ambient, Ambient, PhongMaterial,m_Properties.m_Ambient, Color3),
			UNIFORM(material.diffuse, Diffuse, PhongMaterial, m_Properties.m_Diffuse, Color3),
			UNIFORM(material.specular, Specular, PhongMaterial, m_Properties.m_Specular, Color3),
			UNIFORM(material.emission, Emission, PhongMaterial, m_Properties.m_Emission, Color3),
			UNIFORM(material.shininess, Shininess, PhongMaterial, m_Properties.m_Shininess, Float),
			UNIFORM(material.opacity, Opacity, PhongMaterial, m_Properties.m_Opacity, Float),
			UNIFORM(material.cutoff, Cut Off, PhongMaterial, m_Properties.m_CutOff, Bool),
			UNIFORM(material.doublesided, Double Sided, PhongMaterial, m_Properties.m_Doublesided, Bool),
			UNIFORM(material.useTextureAsAlpha, Use Diffuse As Alpha, PhongMaterial, m_Properties.m_UseDiffuseAsAlpha, Bool),
			SAMPLERUNIFORM(material.diffuseTexture, Diffuse Texture, PhongMaterial, m_Properties.m_DiffuseTexture, Sampler,1),
			SAMPLERUNIFORM(material.specularTexture, Specular Texture, PhongMaterial, m_Properties.m_SpecularTexture, Sampler, 2),
			SAMPLERUNIFORM(material.emissionTexture, Emission Texture, PhongMaterial, m_Properties.m_EmissionTexture, Sampler, 3),
			SAMPLERUNIFORM(material.normalTexture, Normal Texture, PhongMaterial, m_Properties.m_NormalTexture, Sampler, 4),
			SAMPLERUNIFORM(material.displacementTexture, Displacment Texture, PhongMaterial, m_Properties.m_DisplacementTexture, Sampler, 5),
			UNIFORM(material.heightScale, Height Scale, PhongMaterial, m_Properties.m_HeightScale, Float),
			UNIFORM(material.discardEdges, Discard Edges, PhongMaterial, m_Properties.m_DiscardEdges, Bool),
			UNIFORM(material.tiling, Tiling, PhongMaterial, m_Properties.m_TextureTiling, Vec2)
			});
	}

	GridMaterial::GridMaterial()
	{
		m_Shader = AssetManager::Get<Shader>("2DGrid");

		m_ShaderUniforms.Add({
			UNIFORM(scale, Scale, GridMaterial, m_Properties.m_Scale, Float),
			UNIFORM(resolution, Resolution, GridMaterial, m_Properties.m_Resolution, Float),
			UNIFORM(linecolor, Line Color, GridMaterial, m_Properties.m_LineColor, Color4),
			UNIFORM(backgroundColor, Background Color, GridMaterial, m_Properties.m_BackgroundColor, Color4)
		});
	}

	ToonMaterial::ToonMaterial()
	{
		m_Shader = AssetManager::Get<Shader>("Toon");

		m_ShaderUniforms.Add({
			SAMPLERUNIFORM(material.diffuseTexture, Diffuse, ToonMaterial, m_Properties.m_DiffuseTexture, Sampler, 1),
			SAMPLERUNIFORM(material.emissionTexture, Emission, ToonMaterial, m_Properties.m_EmissionTexture, Sampler, 2),
			UNIFORM(material.ambient, Ambient, ToonMaterial , m_Properties.m_Ambient, Color3),
			UNIFORM(material.diffuse, Diffuse, ToonMaterial , m_Properties.m_Diffuse, Color3),
			UNIFORM(material.emission, Emission, ToonMaterial , m_Properties.m_Emission, Color3),
			UNIFORM(material.specular, Specular, ToonMaterial , m_Properties.m_Specular, Color3),
			UNIFORM(material.shininess, Shininess, ToonMaterial, m_Properties.m_Shininess, Float),
			UNIFORM(material.opacity, Opacity, ToonMaterial, m_Properties.m_Opacity, Float),
			UNIFORM(material.cutoff, Cut Off, ToonMaterial, m_Properties.m_CutOff, Bool),
			UNIFORM(material.useTextureAsAlpha, Use Diffuse As Alpha, ToonMaterial, m_Properties.m_UseDiffuseAsAlpha, Bool),
			UNIFORM(material.tiling, Tiling, ToonMaterial, m_Properties.m_Tiling, Vec2)
			});
	}

	PostProcessingMaterial::PostProcessingMaterial()
	{
		m_Shader = AssetManager::Get<Shader>("HDRPostProcessing");
	}

}