#include "BHivePCH.h"
#include "Material.h"
#include "Managers/AssetManagers.h"

namespace BHive
{

	void Material::Render()
	{
		if (m_Shader)
		{
			m_Shader->Bind();

			OnShaderBind(m_Shader);
		}

		/*if (m_Texture)
		{
			m_Texture->Bind();
		}*/

	}

	void Material::OnImGuiRender()
	{
		ImGui::Separator();
		ImGui::Text("Material");
		ImGui::SameLine();
		if (ImGui::BeginCombo("", *m_Texture->GetName(), ImGuiComboFlags_NoArrowButton))
		{
			for (int n = 0; n < TextureManager::GetNames().size(); n++)
			{
				std::string name = TextureManager::GetNames()[n];
				if (ImGui::Selectable(*name, name == m_Texture->GetName()))
				{
					m_Texture = TextureManager::Get(name);
				}
			}
			ImGui::EndCombo();
		}
	}

	void DefaultMaterial::OnImGuiRender()
	{
		Material::OnImGuiRender();

		ImGui::ColorEdit3("Ambient Color", *m_AmbientColor);
		ImGui::ColorEdit3("Diffuse Color##", *m_DiffuseColor);
		ImGui::DragFloat("Transparency", &m_Transparency, 0.01f, 0.0f, 1.0f);
		ImGui::DragFloat2("Texture Tiling##", *m_TextureTiling, 0.1f);
	}

	void DefaultMaterial::OnShaderBind(Ref<Shader>& shader)
	{
		shader->SetVec3("material.ambient", m_AmbientColor);
		shader->SetVec3("material.diffuse", m_DiffuseColor);
		shader->SetFloat("material.transparency", 1.0f - m_Transparency);
		shader->SetVec2("material.tiling", m_TextureTiling);
	}

	void LambertMaterial::OnImGuiRender()
	{
		DefaultMaterial::OnImGuiRender();
	}

	void LambertMaterial::OnShaderBind(Ref<Shader>& shader)
	{
		DefaultMaterial::OnShaderBind(shader);
	}

	void PhongMaterial::OnImGuiRender()
	{
		ImGui::Separator();
		ImGui::Text("Phong Material");
		ImGui::Separator();
		
		static std::string dtextureName = "None";
		if (ImGui::BeginCombo("Diffuse texture", *dtextureName, ImGuiComboFlags_NoArrowButton))
		{
			for (int n = 0; n < TextureManager::GetNames().size(); n++)
			{
				std::string name = TextureManager::GetNames()[n];

				if (ImGui::Selectable(*name, name == dtextureName))
				{
					m_DiffuseTexture = TextureManager::Get(name);
					dtextureName = m_DiffuseTexture->GetName();
				}
			}
			ImGui::EndCombo();
		}
		
		static std::string stextureName = "None";
		if (ImGui::BeginCombo("Specular Texture", *stextureName, ImGuiComboFlags_NoArrowButton))
		{
			for (int n = 0; n < TextureManager::GetNames().size(); n++)
			{
				std::string name = TextureManager::GetNames()[n];

				if (ImGui::Selectable(*name, name == stextureName))
				{
					m_SpecularTexture = TextureManager::Get(name);
					stextureName = m_SpecularTexture->GetName();
				}
			}
			ImGui::EndCombo();
		}
		
		static std::string etextureName = "None";
		if (ImGui::BeginCombo("Emission Texture", *etextureName, ImGuiComboFlags_NoArrowButton))
		{
			for (int n = 0; n < TextureManager::GetNames().size(); n++)
			{
				std::string name = TextureManager::GetNames()[n];

				if (ImGui::Selectable(*name, name == etextureName))
				{
					m_EmissionTexture = TextureManager::Get(name);
					etextureName = m_EmissionTexture->GetName();
				}
			}
			ImGui::EndCombo();
		}
		
		ImGui::ColorEdit3("Ambient Color", *m_Ambient);
		ImGui::ColorEdit3("Diffuse Color", *m_Diffuse);
		ImGui::ColorEdit3("Specular Color", *m_Specular);
		ImGui::ColorEdit3("Emission Color", *m_Emission);
		ImGui::DragFloat("Shininess", &m_Shininess, 0.01f, 0.0f, 60.0f);
		ImGui::DragFloat("Transparency", &m_Transparency, 0.01f, 0.0f, 1.0f);
		ImGui::DragFloat2("Texture Tiling", *m_TextureTiling, 0.1f);
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

	void GridMaterial::OnImGuiRender()
	{
		ImGui::DragFloat("Grid Scale", &m_Scale, .01f, 0.0f, 1000.0f);
		ImGui::DragFloat("Grid Resolution", &m_Resolution, .01f, 0.0f, 1.0f);
		ImGui::ColorEdit4("Grid Color", *m_LineColor);
		ImGui::ColorEdit4("Grid Background Color", *m_BackgroundColor);
	}

	void GridMaterial::OnShaderBind(Ref<Shader>& shader)
	{
		m_Shader->SetFloat("scale", m_Scale);
		m_Shader->SetFloat("resolution", m_Resolution);
		m_Shader->SetVec4("lineColor", m_LineColor);
		m_Shader->SetVec4("backgroundColor", m_BackgroundColor);
	}

}