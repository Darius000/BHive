#pragma once


#include "ImGuiPanel.h"
#include "BHive/Assets/Asset.h"
#include "ComponentDetails/PropertyDetailsBuilder.h"


namespace BHive
{
	
	class Editor : public ImGuiPanel
	{
	public:
		Editor(const std::string& label, IAssetType* asset, uint64 id = 0);

		void OnRenderMenuBar() override;
		void OnRenderWindow() override;

	protected:
		IAssetType* m_Asset;
		PropertyDetailsBuilder detailsBuilder;
	};

}