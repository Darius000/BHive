#pragma once

#include "Editors/ImGuiPanel.h"
#include "ComponentDetails/PropertyDetailsBuilder.h"

namespace BHive
{
	class PropertiesPanel : public ImGuiPanel
	{

	public:
		PropertiesPanel(uint64 id = 0);

		void OnRenderMenuBar() override;

		void OnRenderWindow() override;

	private:
		void DrawEnityComponents(Entity entity);
		void DrawAddComponentsButton(Entity entity);

		PropertyDetailsBuilder m_DetailsBuilder;
	};
}