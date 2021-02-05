#include "BHivePCH.h"
#include "PropertiesPanel.h"
#include "SceneHierarchyPanel.h"
#include "EditorClassRegistry.h"


namespace BHive
{

	PropertiesPanel::PropertiesPanel(uint64 id)
		:ImGuiPanel("Properties", ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_AlwaysVerticalScrollbar, id)
	{

	}

	void PropertiesPanel::OnRenderMenuBar()
	{
		auto selectedEntity = SceneHierarchyPanel::GetSelectedEntity();

		if (selectedEntity)
		{
			DrawAddComponentsButton(selectedEntity);
		}
	}

	void PropertiesPanel::OnRenderWindow()
	{
		auto selectedEntity = SceneHierarchyPanel::GetSelectedEntity();

		if (selectedEntity)
		{
			m_DetailsBuilder.SetEntity(selectedEntity);
			DrawEnityComponents(selectedEntity);
		}
	}

	void PropertiesPanel::DrawEnityComponents(Entity entity)
	{
		if (entity.HasComponent<TagComponent>())
		{
			auto DetailsCustomization = EditorClassRegistry::GetDetailsCustomizationInstance("TagComponent");
			DetailsCustomization->CreateCustomizedDetails(m_DetailsBuilder);
		}

		if (entity.HasComponent<TransformComponent>())
		{
			auto DetailsCustomization = EditorClassRegistry::GetDetailsCustomizationInstance("TransformComponent");
			DetailsCustomization->CreateCustomizedDetails(m_DetailsBuilder);
		}

		if (entity.HasComponent<DirectionalLightComponent>())
		{
			auto DetailsCustomization = EditorClassRegistry::GetDetailsCustomizationInstance("DirectionalLightComponent");
			DetailsCustomization->CreateCustomizedDetails(m_DetailsBuilder);
		}

		if (entity.HasComponent<PointLightComponent>())
		{
			auto DetailsCustomization = EditorClassRegistry::GetDetailsCustomizationInstance("PointLightComponent");
			DetailsCustomization->CreateCustomizedDetails(m_DetailsBuilder);
		}

		if (entity.HasComponent<SpotLightComponent>())
		{
			auto DetailsCustomization = EditorClassRegistry::GetDetailsCustomizationInstance("SpotLightComponent");
			DetailsCustomization->CreateCustomizedDetails(m_DetailsBuilder);
		}

		if (entity.HasComponent<CameraComponent>())
		{
			auto DetailsCustomization = EditorClassRegistry::GetDetailsCustomizationInstance("CameraComponent");
			DetailsCustomization->CreateCustomizedDetails(m_DetailsBuilder);
		}

		if (entity.HasComponent<RenderComponent>())
		{
			auto DetailsCustomization = EditorClassRegistry::GetDetailsCustomizationInstance("RenderComponent");
			DetailsCustomization->CreateCustomizedDetails(m_DetailsBuilder);
		}

		if (entity.HasComponent<NativeScriptComponent>())
		{
			auto DetailsCustomization = EditorClassRegistry::GetDetailsCustomizationInstance("NativeScriptComponent");
			DetailsCustomization->CreateCustomizedDetails(m_DetailsBuilder);
		}
	}

	void PropertiesPanel::DrawAddComponentsButton(Entity entity)
	{
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(.3f, .8f, .3f, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(.5f, .8f, .5f, 1.0f));
		if (ImGui::Button("Add Component"))
		{
			ImGui::OpenPopup("Components");
		}
		ImGui::PopStyleColor(2);

		if (ImGui::BeginPopup("Components"))
		{
			for (auto Class : ClassRegistry::GetClassRegistryList())
			{
				const char* name = Class;
				if (ImGui::Selectable(name))
				{
					if (name == "TransformComponent")
					{
						entity.AddComponent<TransformComponent>();
					}
					else if (name == "RenderComponent")
					{
						entity.AddComponent<RenderComponent>();
					}
					else if (name == "PointLightComponent")
					{
						entity.AddComponent<PointLightComponent>();
					}
					else if (name == "TagComponent")
					{
						entity.AddComponent<TagComponent>();
					}
					else if (name == "DirectionalLightComponent")
					{
						entity.AddComponent<DirectionalLightComponent>();
					}
					else if (name == "CameraComponent")
					{
						entity.AddComponent<CameraComponent>();
					}
					else if (name == "NativeScriptComponent")
					{
						entity.AddComponent<NativeScriptComponent>();
					}

				}
			}

			ImGui::EndPopup();
		}
	}
}