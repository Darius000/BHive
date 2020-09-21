#pragma once

#include "BHive.h"
#include "BHive/Core/ImGuiPanel.h"

namespace BHive
{
	class IFileBrowser;

	class AssetBrowserPanel : public ImGuiPanel
	{
	public:
		AssetBrowserPanel();
		AssetBrowserPanel(unsigned int columns , ImGuiWindowFlags flags = 0);

		void OnRenderWindow() override;

		void DrawAssetIcon(Asset* asset);

	private:
		Asset* SelectedAsset = nullptr;

		ImVec2 IconSize		= ImVec2(100, 100);
		float IconSpacing	= 5.0f;
		unsigned int m_Columns = 0;

		IFileBrowser* m_FileBrowser = nullptr;
	};
}