#pragma once

#include "BHive.h"
#include "../Editors/EditorStack.h"
#include "Renderer/Texture.h"
#include "Layers/ImGuiLayer.h"

namespace BHive
{
	class IFileBrowser;

	class AssetBrowserPanel : public ImGuiPanel
	{
	public:
		AssetBrowserPanel();
		AssetBrowserPanel(unsigned int columns , ImGuiWindowFlags flags = 0);


		void OnImGuiRender() override;

		void DrawAssetIcon(Asset* asset);

	private:
		Asset* SelectedAsset = nullptr;

		ImVec2 IconSize		= ImVec2(100, 100);
		float IconSpacing	= 5.0f;
		ImGuiWindowFlags m_Flags = 0;
		unsigned int m_Columns = 0;

		IFileBrowser* m_FileBrowser = nullptr;
	};
}