#pragma once

#include "BHive.h"
#include "Editors/ImGuiPanel.h"
#include "ComponentDetails/PropertyDetailsBuilder.h"

namespace BHive
{
	class SceneHierarchyPanel : public ImGuiPanel
	{
	public:
		SceneHierarchyPanel(Scene* context);

		//Set the scene the panel should display
		void SetContext(Scene* context);

		void OnRenderWindow() override;

	private:
		//Draw entity dropdown node in panel
		void DrawEntityNode(Entity entity);
		void DrawEnityComponents(Entity entity);
		void DrawAddRemoveComponents(Entity entity);

	private:
		Scene* m_SceneContext = nullptr;
		Entity m_SelectedContext;
		PropertyDetailsBuilder m_DetailsBuilder;
	};
}