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
			UNIFORM("material.ambient", "Ambient", DefaultMaterial, m_AmbientColor, ShaderUniformType::Color3),
			UNIFORM("material.diffuse", "Diffuse", DefaultMaterial, m_DiffuseColor, ShaderUniformType::Color3),
			UNIFORM("material.opacity", "Opacity", DefaultMaterial, m_Opacity, ShaderUniformType::Float),
			UNIFORM("material.tiling", "Tiling", DefaultMaterial, m_TextureTiling, ShaderUniformType::Vec2)
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
			UNIFORM("material.ambient", "Ambient", PhongMaterial, m_Ambient, ShaderUniformType::Color3),
			UNIFORM("material.diffuse", "Diffuse", PhongMaterial, m_Diffuse, ShaderUniformType::Color3),
			UNIFORM("material.specular", "Specular", PhongMaterial, m_Specular, ShaderUniformType::Color3),
			UNIFORM("material.emission", "Emission", PhongMaterial, m_Emission, ShaderUniformType::Color3),
			UNIFORM("material.shininess", "Shininess", PhongMaterial, m_Shininess, ShaderUniformType::Float),
			UNIFORM("material.opacity", "Opacity", PhongMaterial, m_Opacity, ShaderUniformType::Float),
			UNIFORM("material.cutoff", "Cut Off", PhongMaterial, m_CutOff, ShaderUniformType::Bool),
			UNIFORM("material.useTextureAsAlpha", "Use Diffuse As Alpha", PhongMaterial, m_UseDiffuseAsAlpha, ShaderUniformType::Bool),
			SAMPLERUNIFORM("material.diffuseTexture", "Diffuse Texture", PhongMaterial, m_DiffuseTexture, ShaderUniformType::Sampler,1),
			SAMPLERUNIFORM("material.specularTexture", "Specular Texture", PhongMaterial, m_SpecularTexture, ShaderUniformType::Sampler, 2),
			SAMPLERUNIFORM("material.emissionTexture", "Emission Texture", PhongMaterial, m_EmissionTexture, ShaderUniformType::Sampler, 3),			
			UNIFORM("material.tiling", "Tiling", PhongMaterial, m_TextureTiling, ShaderUniformType::Vec2)
			});
	}

	GridMaterial::GridMaterial()
	{
		m_Shader = AssetManager::Get<Shader>("2DGrid");

		m_ShaderUniforms.Add({
			UNIFORM("scale", "Scale", GridMaterial, m_Scale, ShaderUniformType::Float),
			UNIFORM("resolution", "Resolution", GridMaterial, m_Resolution, ShaderUniformType::Float),
			UNIFORM("linecolor", "Line Color", GridMaterial, m_LineColor, ShaderUniformType::Color4),
			UNIFORM("backgroundColor", "Background COlor", GridMaterial, m_BackgroundColor, ShaderUniformType::Color4)
		});
	}
}