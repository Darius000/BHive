#include "SceneHierarchyPanel.h"

#include <imgui/imgui.h>

namespace BHive
{

	SceneHierarchyPanel::SceneHierarchyPanel(Scene* context)
		:ImGuiPanel("Scene Hierarchy")
	{
		SetContext(context);
	}

	void SceneHierarchyPanel::SetContext(Scene* context)
	{
		m_SceneContext = context;
	}

	void SceneHierarchyPanel::OnImGuiRender()
	{
		if (!m_SceneContext || !m_isOpen) return;

		ImGui::Begin(m_Label, &m_isOpen);

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

		ImGui::End();

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
			auto DetailsCustomization = ClassPropertyRegistry::GetDetailsCustomizationInstance("TagComponent");
			DetailsCustomization->CreateCustomizedDetails(m_DetailsBuilder);
		}

		if (entity.HasComponent<TransformComponent>())
		{
			auto DetailsCustomization = ClassPropertyRegistry::GetDetailsCustomizationInstance("TransformComponent");
			DetailsCustomization->CreateCustomizedDetails(m_DetailsBuilder);
		}

		if (entity.HasComponent<DirectionalLightComponent>())
		{
			auto DetailsCustomization = ClassPropertyRegistry::GetDetailsCustomizationInstance("DirectionalLightComponent");
			DetailsCustomization->CreateCustomizedDetails(m_DetailsBuilder);
		}

		if (entity.HasComponent<PointLightComponent>())
		{
			auto DetailsCustomization = ClassPropertyRegistry::GetDetailsCustomizationInstance("PointLightComponent");
			DetailsCustomization->CreateCustomizedDetails(m_DetailsBuilder);
		}

		if (entity.HasComponent<SpotLightComponent>())
		{
			auto DetailsCustomization = ClassPropertyRegistry::GetDetailsCustomizationInstance("SpotLightComponent");
			DetailsCustomization->CreateCustomizedDetails(m_DetailsBuilder);
		}

		if (entity.HasComponent<CameraComponent>())
		{
			auto DetailsCustomization = ClassPropertyRegistry::GetDetailsCustomizationInstance("CameraComponent");
			DetailsCustomization->CreateCustomizedDetails(m_DetailsBuilder);
		}

		if (entity.HasComponent<RenderComponent>())
		{
			auto DetailsCustomization = ClassPropertyRegistry::GetDetailsCustomizationInstance("RenderComponent");
			DetailsCustomization->CreateCustomizedDetails(m_DetailsBuilder);
		}
	}
}