#pragma once

#include "BHive.h"
#include "Editors/ImGuiPanel.h"
#include "ComponentDetails/PropertyDetailsBuilder.h"

namespace BHive
{
	class SceneHierarchyPanel : public ImGuiPanel
	{
	public:
		SceneHierarchyPanel(Scene* context, uint64 id = 0);

		//Set the scene the panel should display
		void SetContext(Scene* context);

		void OnRenderMenuBar() override;
		void OnRenderWindow() override;

		static Entity GetSelectedEntity() { return m_SelectedContext; }

	private:
		//Draw entity dropdown node in panel
		void DrawEntityNode(Entity entity);
		

	private:
		Scene* m_SceneContext = nullptr;
		static Entity m_SelectedContext;
		PropertyDetailsBuilder m_DetailsBuilder;
	};
}