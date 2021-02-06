#pragma once

#include "BHive.h"
#include "Editors/ImGuiPanel.h"

namespace BHive
{
	class IFileBrowser;

	class AssetBrowserPanel : public ImGuiPanel
	{
	public:
		AssetBrowserPanel(uint64 id = 0);
		AssetBrowserPanel(unsigned int columns , ImGuiWindowFlags flags = 0, uint64 id = 0);

		void OnRenderMenuBar() override;
		void OnRenderWindow() override;

		void DrawAssetIcon(IAssetType* asset);

		/* Begin ImGui panel events*/
		bool OnKeyPressed(KeyPressedEvent& e) override;

		bool OnMouseScrolled(MouseScrolledEvent& e) override;

		bool OnKeyReleased(KeyReleasedEvent& e) override;

		bool OnMouseMoved(MouseMovedEvent& e) override;

		bool OnMouseButtonPressed(MouseButtonPressedEvent& e) override;

		bool OnMouseButtonReleased(MouseButtonReleasedEvent& e) override;

		/*End ImGuiPanel Events*/

	private:
		void ToggleFilter(const std::string& filter, bool enabled);
		void RemoveFilter(const std::string& filter);
		uint64 GetTextLimit(const std::string& text, float limit);

	private:
		IAssetType* SelectedAsset = nullptr;

		ImVec2 IconSize		= ImVec2(100, 100);
		float IconSpacing	= 5.0f;
		unsigned int m_Columns = 0;

		std::unordered_map<std::string, bool> m_Assetfilers;
		std::vector<std::string> m_CurrentFilters;
		std::string m_SearchFilter;

		bool m_CtrlPressed = false;
	};
}