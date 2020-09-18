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

			OnShaderBind(m_Shader);
		}

		if (m_Texture)
		{
			m_Shader->SetInt("material.diffuseTexture", 1);
			m_Texture->Bind(1);
		}
	}

	DefaultMaterial::DefaultMaterial()
	{
		m_Shader = AssetManager::Get<Shader>("Default");
	}

	void DefaultMaterial::OnShaderBind(Ref<Shader>& shader)
	{

		shader->SetVec3("material.ambient", m_AmbientColor);
		shader->SetVec3("material.diffuse", m_DiffuseColor);
		shader->SetFloat("material.transparency", 1.0f - m_Transparency);
		shader->SetVec2("material.tiling", m_TextureTiling);
	}

	void LambertMaterial::OnShaderBind(Ref<Shader>& shader)
	{
		DefaultMaterial::OnShaderBind(shader);
	}

	LambertMaterial::LambertMaterial()
	{
		m_Shader = AssetManager::Get<Shader>("Lambert");
	}

	void PhongMaterial::OnShaderBind(Ref<Shader>& shader)
	{
		shader->SetVec3("material.ambient", m_Ambient);
		shader->SetVec3("material.diffuse", m_Diffuse);
		shader->SetVec3("material.specular", m_Specular);
		shader->SetVec3("material.emission", m_Emission);
		shader->SetFloat("material.shininess", m_Shininess);
		shader->SetFloat("material.transparency", 1.0f - m_Transparency);
		shader->SetVec2("material.tiling", m_TextureTiling);
		if(m_DiffuseTexture) 
		{
			shader->SetInt("material.diffuseTexture", 0);
			m_DiffuseTexture->Bind(0);
			
		}
		if (m_SpecularTexture)
		{
			
			shader->SetInt("material.specularTexture", 1);
			m_SpecularTexture->Bind(1);
		}
		if (m_EmissionTexture)
		{
		
			shader->SetInt("material.emissionTexture", 2);
			m_EmissionTexture->Bind(2);
			
		}
	}

	PhongMaterial::PhongMaterial()
	{
		m_Shader = AssetManager::Get<Shader>("Phong");
	}

	GridMaterial::GridMaterial()
	{
		m_Shader = AssetManager::Get<Shader>("2DGrid");
	}

	void GridMaterial::OnShaderBind(Ref<Shader>& shader)
	{
		m_Shader->SetFloat("scale", m_Scale);
		m_Shader->SetFloat("resolution", m_Resolution);
		m_Shader->SetVec4("lineColor", m_LineColor);
		m_Shader->SetVec4("backgroundColor", m_BackgroundColor);
	}

}