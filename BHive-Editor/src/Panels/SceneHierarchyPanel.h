#pragma once

#include "BHive.h"
#include "../Editors/Editor.h"
#include "BHive/Core/ComponentDetails/DetailsCustomization.h"

namespace BHive
{
	class SceneHierarchyPanel : public ImGuiPanel
	{
	public:
		SceneHierarchyPanel(Scene* context);

		//Set the scene the panel should display
		void SetContext(Scene* context);

		void OnImGuiRender() override;

	private:
		//Draw entity dropdown node in panel
		void DrawEntityNode(Entity entity);
		void DrawEnityComponents(Entity entity);

	private:
		Scene* m_SceneContext = nullptr;
		Entity m_SelectedContext;
		DetailsBuilder m_DetailsBuilder;
	};
}