#include "AssetBrowserPanel.h"
#include "../PopUps/FileBrowser.h"

namespace BHive
{

	void AssetBrowserPanel::DrawAssetIcon(Asset* asset)
	{
		ImVec4 BgColor = asset == SelectedAsset ? ImVec4(1, 1, 0, 1) : ImVec4(0, 0, 0, 0);

		ImGui::BeginGroup();
		//ImGui::ImageButton((void*)asset->GetThumnailID(), IconSize, ImVec2(0, 1), ImVec2(1, 0), 0, BgColor);
		ImGui::ImageButton((void*)((Texture2D*)asset)->GetRendererID(), IconSize, ImVec2(0, 1), ImVec2(1, 0), 0, BgColor);
		ImGui::Text(asset->GetName().c_str());
		ImGui::EndGroup();
		if (ImGui::BeginPopupContextItem("Asset Popup"))
		{
			if (ImGui::MenuItem("Edit"))
			{
				EditorStack::OpenEditorForAsset(asset);
			}

			ImGui::EndPopup();
		}

		if (ImGui::IsItemClicked((int)MouseButton::Left) || ImGui::IsItemClicked((int)MouseButton::Right))
		{
			SelectedAsset = asset;
		}
	}

	AssetBrowserPanel::AssetBrowserPanel() 
		: ImGuiPanel("Content Browser"), m_Columns(0), m_Flags(0)
	{
		m_FileBrowser = new IFileBrowser();
	}

	AssetBrowserPanel::AssetBrowserPanel(unsigned int columns, ImGuiWindowFlags flags)
		:ImGuiPanel("Content Browser") , m_Columns(columns), m_Flags(flags)
	{
		m_FileBrowser = new IFileBrowser();
	}

	void AssetBrowserPanel::OnImGuiRender()
	{
		ImGui::Begin(m_Label, &m_isOpen, m_Flags);

		

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(100.0f, 50.0f));
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.5f, 1.0f, 0.5f, 1.0f));
		if (ImGui::BeginMenuBar())
		{
			if (ImGui::Button("Import"))
			{
				m_FileBrowser->OpenPopup();
			}

			m_FileBrowser->OnImGuiRender();

			ImGui::EndMenuBar();
		}

		ImGui::PopStyleColor(1);
		ImGui::PopStyleVar(ImGuiStyleVar_WindowPadding);

		ImGuiIO io = ImGui::GetIO();
		if (ImGui::IsWindowFocused() && ImGui::IsWindowHovered() && ImGui::IsKeyDown((int)KeyCode::Left_control))
		{
			float mousewheel = io.MouseWheel * 5.0f;

			IconSize.x = MathLibrary::Clamp(IconSize.x + mousewheel, 20.0f, 200.0f);
			IconSize.y = MathLibrary::Clamp(IconSize.y + mousewheel, 20.0f, 200.0f);
		}

		ImVec2 ContentBrowserSize = ImGui::GetContentRegionAvail();

		size_t i = 0;
		for (auto& asset : AssetManager::GetAssets<Texture2D>())
		{
			auto AvailableWidth = (int32)floor(ContentBrowserSize.x);
			auto IconWidth = (int32)floor(IconSize.x - (IconSpacing));

			int32 Columns = 0;

			if (AvailableWidth <= 0 || IconWidth <= 0 || (AvailableWidth / IconWidth <= 0))
			{
				Columns = 1;
			}
			else
			{
				if (m_Columns == 0)
					Columns = AvailableWidth / IconWidth;
				else
					Columns = m_Columns;
			}

			//break in the case available region is smaller then the icon size
			if (Columns <= 0) break;

			if (i % Columns != 0) ImGui::SameLine(0.0f, IconSpacing);

			ImGui::PushID((uint32*)asset.second.get());

			DrawAssetIcon(asset.second.get());

			if (ImGui::IsMouseDoubleClicked((int)MouseButton::Left) && ImGui::IsItemActive())
			{
				SelectedAsset = asset.second.get();

				EditorStack::OpenEditorForAsset(asset.second.get());
			}

			ImGui::PopID();
			i++;
		}


		ImGui::End();
	}

}