#include "SceneHierarchyPanel.h"
#include "EditorClassRegistry.h"
#include <imgui/imgui.h>

namespace BHive
{

	SceneHierarchyPanel::SceneHierarchyPanel(Scene* context)
		:ImGuiPanel("Scene Hierarchy", 0)
	{
		SetContext(context);
	}

	void SceneHierarchyPanel::SetContext(Scene* context)
	{
		m_SceneContext = context;
	}

	void SceneHierarchyPanel::OnRenderWindow()
	{
		if (!m_SceneContext || !m_isOpen) return;

		m_SceneContext->m_Registry.each([&](auto entityID)
		{
			Entity entity{ entityID, m_SceneContext };
			DrawEntityNode(entity);

		});

		if (ImGui::IsMouseDown((int)MouseButton::Left)
			&& ImGui::IsWindowHovered())
		{
			m_SelectedContext = {};
		}


		ImGui::Begin("Properties");
		if (m_SelectedContext)
		{
			DrawEnityComponents(m_SelectedContext);
		}
		ImGui::End();
	}

	void SceneHierarchyPanel::DrawEntityNode(Entity entity)
	{
		auto& tag = entity.GetComponent<TagComponent>().Tag;

		ImGuiTreeNodeFlags flags = ((m_SelectedContext == entity) ? ImGuiTreeNodeFlags_Selected : 0) |
			ImGuiTreeNodeFlags_OpenOnArrow;
		bool opened = ImGui::TreeNodeEx((void*)(uint32*)&entity, flags, tag.c_str());
		if (ImGui::IsItemClicked())
		{
			m_SelectedContext = entity;
			m_DetailsBuilder.SetEntity(m_SelectedContext);
		}

		if (opened)
		{
			ImGui::TreePop();
		}
	}

	void SceneHierarchyPanel::DrawEnityComponents(Entity entity)
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

		DrawAddRemoveComponents(entity);
	}

	void SceneHierarchyPanel::DrawAddRemoveComponents(Entity entity)
	{

		if (ImGui::Button("Add Component"))
		{
			ImGui::OpenPopup("Components");
		}


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