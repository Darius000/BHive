#include "BHivePCH.h"
#include <glad/glad.h>
#include "RenderComponent.h"
#include "BHive/Renderer/Renderer.h"
#include "Managers/AssetManagers.h"


namespace BHive
{
	void RenderComponent::Draw()
	{
		if (m_Texture)
		{
			m_Texture->Bind();
		}

		if (m_Model)
		{
			m_Model->Render();
		}
	}


	void RenderComponent::OnImguiRender()
	{
		ImGui::Separator();
		ImGui::Text("Texture");
		ImGui::Image((void*)m_Texture->GetRendererID(), ImVec2(100.0f, 100.0f), ImVec2(0, 1), ImVec2(1, 0));	
		ImGui::SameLine();
		if (ImGui::BeginCombo("##Textures", *m_Texture->GetName(), ImGuiComboFlags_NoArrowButton))
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
}