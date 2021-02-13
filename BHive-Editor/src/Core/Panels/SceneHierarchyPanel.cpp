#include "SceneHierarchyPanel.h"
#include "EditorClassRegistry.h"
#include <imgui/imgui.h>
#include <imgui/imgui_internal.h>

namespace BHive
{

	SceneHierarchyPanel::SceneHierarchyPanel(Scene* context, uint64 id)
		:ImGuiPanel("Scene Hierarchy", ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_AlwaysVerticalScrollbar, id)
	{
		SetContext(context);
	}

	void SceneHierarchyPanel::SetContext(Scene* context)
	{
		m_SceneContext = context;
	}

	void SceneHierarchyPanel::OnRenderMenuBar()
	{
		//Add buttons to add or delete entity
		//Create entity and set it as the selected
		if (ImGui::Button("Add Entity"))
		{
			CreateNewEmptyEntity();
		}

		if (ImGui::Button("Delete Entity"))
		{
			if(m_SelectedContext) m_SelectedContext.Destroy();
		}
	}

	void SceneHierarchyPanel::OnRenderWindow()
	{
		if (!m_SceneContext || !IsOpen()) return;

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

		//Right click on blank space
		if (ImGui::BeginPopupContextWindow((const char*)0, 1, false))
		{
			if (ImGui::MenuItem("Create Entity"))
			{
				CreateNewEmptyEntity();
			}

			ImGui::EndPopup();
		}
	}

	void SceneHierarchyPanel::DrawEntityNode(Entity entity)
	{
		auto& tag = entity.GetComponent<TagComponent>().Tag;
		auto id = std::to_string(entity.GetID());

		ImGuiTreeNodeFlags flags = ((m_SelectedContext == entity) ? ImGuiTreeNodeFlags_Selected : 0) |
			ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_SpanAvailWidth;
		bool opened = ImGui::TreeNodeEx(id.c_str(), flags, tag.c_str());

		if (ImGui::IsItemClicked((int)MouseButton::Left) || ImGui::IsItemClicked((int)MouseButton::Right))
		{
			m_SelectedContext = entity;
			m_DetailsBuilder.SetEntity(m_SelectedContext);
		}

		//Get the id of the entity as the id
		if (ImGui::BeginPopupContextItem(id.c_str()))
		{
			if (ImGui::MenuItem("Delete Entity"))
				m_SelectedContext.Destroy();

			ImGui::EndPopup();
		}

		if (opened)
		{
			ImGui::TreePop();
		}

		if (m_SelectedContext.IsBeingDestroyed() && m_SelectedContext == entity)
		{
			m_SceneContext->DeleteEntity(entity);
			m_SelectedContext = {};
		}
	}

	void SceneHierarchyPanel::CreateNewEmptyEntity()
	{
		auto& newEntity = m_SceneContext->CreateEntity("Empty Entity");
		m_SelectedContext = newEntity;
	}

	Entity SceneHierarchyPanel::m_SelectedContext;
}