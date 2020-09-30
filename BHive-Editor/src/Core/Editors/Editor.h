#pragma once


#include "ImGuiPanel.h"
#include "BHive/Renderer/Asset.h"
#include "ComponentDetails/PropertyDetailsBuilder.h"


namespace BHive
{
	
	class Editor : public ImGuiPanel
	{
	public:
		Editor(const std::string& label, Asset* asset)
			:ImGuiPanel(label, ImGuiWindowFlags_MenuBar, true), m_Asset(asset){}

		void OnRenderWindow() override;

	protected:
		Asset* m_Asset;
		PropertyDetailsBuilder detailsBuilder;
	};

}