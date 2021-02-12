#include "AssetBrowserPanel.h"
#include "Editors/Editor.h"
#include "Editors/EditorStack.h"
#include "BHive/Renderer/Texture.h"
#include "BHive/Core/Utils/PlatformUtils.h"

namespace BHive
{

	void AssetBrowserPanel::DrawAssetIcon(IAssetType* asset)
	{
		ImVec4 BgColor = asset == SelectedAsset ? ImVec4(1, 1, 0, 1) : ImVec4(0, 0, 0, 0);
		const std::string& name = asset->GetName();

		ImGui::PushID((uint32*)asset);
		ImGui::BeginGroup();
		auto texture = (Texture*)AssetManager::Get(asset->GetThumbnailName()).get();

		ImGui::Image((void*)*texture, IconSize, ImVec2(0, 1), ImVec2(1, 0), ImVec4(1,1,1,1), BgColor);
		ImGui::SetCursorScreenPos(ImGui::GetItemRectMin());
		ImGui::InvisibleButton(("##" + name).c_str(), {IconSize.x + 2.0f, IconSize.y + 2.0f});

		if (ImGui::IsItemHovered())
		{
			ImGui::BeginTooltip();
			ImGui::SetTooltip("%s", name.c_str());
			ImGui::EndTooltip();
		}

		if (ImGui::IsItemClicked((int)MouseButton::Left) || ImGui::IsItemClicked((int)MouseButton::Right))
		{
			SelectedAsset = asset;
		}

		if (ImGui::IsMouseDoubleClicked((int)MouseButton::Left) && ImGui::IsItemActive())
		{
			SelectedAsset = asset;

			//auto editor = new Editor();
			EditorStack::Get()->OpenPanel<Editor>(asset->GetName(), asset);
		}

		ImGui::PushItemWidth(IconSize.x);
		
		uint64 limit = GetTextLimit(name, IconSize.x);
		ImGui::TextUnformatted(name.c_str(), &name[limit]);
		ImGui::PopItemWidth();
		ImGui::EndGroup();

		if (ImGui::BeginPopupContextItem("Asset Popup"))
		{
			if (ImGui::MenuItem("Edit"))
			{
				//auto editor = new Editor(asset->GetName(), asset);
				EditorStack::Get()->OpenPanel<Editor>(asset->GetName(), asset);
			}

			ImGui::EndPopup();
		}

		
		ImGui::PopID();
	}

	bool AssetBrowserPanel::OnKeyPressed(KeyPressedEvent& e)
	{
		auto key = e.GetKeyCode();
		if (key == KeyCode::Left_control || key == KeyCode::Right_control)
		{
			m_CtrlPressed = true;
		}

		return false;
	}

	bool AssetBrowserPanel::OnMouseScrolled(MouseScrolledEvent& e)
	{
		//If ctrl pressed , zoom icons
		if(m_CtrlPressed == true)
		{ 
			float mousewheel = e.GetYOffset() * 5.0f;

			IconSize.x = MathLibrary::Clamp(IconSize.x + mousewheel, 20.0f, 200.0f);
			IconSize.y = MathLibrary::Clamp(IconSize.y + mousewheel, 20.0f, 200.0f);

			return true;
		}

		return true;
	}

	bool AssetBrowserPanel::OnKeyReleased(KeyReleasedEvent& e)
	{
		auto key = e.GetKeyCode();
		if (key == KeyCode::Left_control || key == KeyCode::Right_control)
		{
			m_CtrlPressed = false;
		}

		return false;
	}

	void AssetBrowserPanel::ToggleFilter(const std::string& filter, bool enabled)
	{
		if (enabled) m_CurrentFilters.push_back(filter);
		else RemoveFromVector(filter, m_CurrentFilters);
	}

	void AssetBrowserPanel::RemoveFilter(const std::string& filter)
	{
		m_Assetfilers[filter] = false;
		RemoveFromVector(filter, m_CurrentFilters);
	}

	uint64 AssetBrowserPanel::GetTextLimit(const std::string& text, float limit)
	{
		size_t lastChar = text.size();
		float textsize = ImGui::CalcTextSize(text.c_str()).x;

		if(textsize > limit)
		{ 
			size_t textLength = text.size();
			float size = textsize / (float)textLength;
			lastChar = 0;
			for (size_t i = 0; i < text.size(); i++)
			{	
				lastChar++;
				float currentSize = size * (float)(lastChar);
				if (currentSize > limit)
				{
					return lastChar - 1;
				}
			}
		}
		
		return (uint64)lastChar;
	}

	void AssetBrowserPanel::ShowImportButton()
	{
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(.3f, .8f, .3f, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(.5f, .8f, .5f, 1.0f));
		if (ImGui::Button("Import"))
		{
			std::string file = FileDialog::OpenFile("All\0*.*\0""Object\0*.obj\0");
			if (!file.empty())
			{
				AssetImporter::Import(file.c_str());
			}
		}

		ImGui::PopStyleColor(2);
	}

	void AssetBrowserPanel::ShowObjectMenuButton()
	{
		if (ImGui::Button("Add New"))
		{
			ImGui::OpenPopup("Object Menu");
		}

		if (ImGui::BeginPopup("Object Menu"))
		{
			NewObjectMenu();

			ImGui::EndPopup();
		}
	}

	void AssetBrowserPanel::NewObjectMenu()
	{
		
	}

	void AssetBrowserPanel::ShowAssetFilters()
	{
		if (ImGui::Button("Asset Filter"))
		{
			ImGui::OpenPopup("Filters");
		}

		if (ImGui::BeginPopup("Filters"))
		{
			for (auto& filterType : m_Assetfilers)
			{
				auto* enabledFilter = &filterType.second;
				const auto& type = filterType.first;

				if (ImGui::Checkbox(type.c_str(), enabledFilter))
				{
					ToggleFilter(type, *enabledFilter);
				}
			}
		
			ImGui::EndPopup();
		}

		for (auto& filter : m_CurrentFilters)
		{
			ImGui::PushID(filter.c_str());
			ImGui::BeginGroup();
			ImGui::Text(filter.c_str());
			ImGui::SameLine();
			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1.0f, 0.0f, 0.0f, 1.0f));
			if (ImGui::Button("X"))
			{
				RemoveFilter(filter);
			}
			ImGui::PopStyleColor();
			ImGui::EndGroup();
			ImGui::PopID();
		}
	}

	void AssetBrowserPanel::ShowSearchBar()
	{
		PropertyDetailsBuilder::SearchBar(m_SearchFilter);
	}

	AssetBrowserPanel::AssetBrowserPanel(uint64 id)
		:AssetBrowserPanel(0, ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_HorizontalScrollbar | ImGuiWindowFlags_AlwaysVerticalScrollbar)
	{
		
	}

	AssetBrowserPanel::AssetBrowserPanel(unsigned int columns, ImGuiWindowFlags flags, uint64 id)
		:ImGuiPanel("Content Browser", flags) , m_Columns(columns)
	{
		m_Assetfilers = { {"Shader", false}, {"Model", false}, {"Texture2D", false}, {"Material", false}
		,{"FontFamily", false}, {"Font", false}};
	}

	void AssetBrowserPanel::OnRenderMenuBar()
	{
		ShowImportButton();
		ShowObjectMenuButton();
		ShowAssetFilters();
		ShowSearchBar();
	}

	void AssetBrowserPanel::OnRenderWindow()
	{
		if (ImGui::IsMouseDown((int)MouseButton::Left)
			&& ImGui::IsWindowHovered())
		{
			SelectedAsset = nullptr;
		}

		float ContentBrowserSize = ImGui::GetWindowContentRegionWidth();

		size_t i = 0;
		for (auto& asset : AssetManager::GetAssets())
		{
			if (!m_CurrentFilters.empty())
			{
				std::string type = asset.second->GetAssetTypeName();
		
				if (FindInVector(type, m_CurrentFilters) == -1)
				{
					continue;
				}
			}

			if (m_SearchFilter.empty() == false)
			{
				auto name = asset.second->GetName();
				if(!PropertyDetailsBuilder::CheckSearchFilter(name, m_SearchFilter)) continue;
			}

			auto AvailableWidth = (int32)floor(ContentBrowserSize - IconSize.x);
			auto IconWidth = (int32)floor(IconSize.x + (IconSpacing));

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

			DrawAssetIcon(asset.second.get());

			i++;
		}
	}

	bool AssetBrowserPanel::OnMouseMoved(MouseMovedEvent& e)
	{
		return false;
	}

	bool AssetBrowserPanel::OnMouseButtonPressed(MouseButtonPressedEvent& e)
	{
		return false;
	}

	bool AssetBrowserPanel::OnMouseButtonReleased(MouseButtonReleasedEvent& e)
	{
		return false;
	}

}