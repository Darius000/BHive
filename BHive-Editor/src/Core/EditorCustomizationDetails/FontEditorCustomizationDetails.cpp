#include "BHivePCH.h"
#include "FontEditorCustomizationDetails.h"
#include "BHive/Font/FontFamily.h"

namespace BHive
{
	void FontEditorCustomizationDetails::CreateCustomizedDetails(PropertyDetailsBuilder& detailsBuilder, IAssetType* asset)
	{
		fontFamily = (FontFamily*)asset;
		detailsBuilderPtr = &detailsBuilder;

		ImGui::PushID(fontFamily->GetName().c_str());

		ImGui::Columns(2);

		//Font List
		ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(.1f, .1f, .1f, 1.0f));
		ImGui::BeginChild("Default Font Family", ImVec2(0, 0), true, ImGuiWindowFlags_AlwaysHorizontalScrollbar);
		ImGui::Text("Default Font Family");
		for (auto& font : fontFamily->m_Fonts)
		{
			CreateFontNode(font.first, font.second);
			ImGui::SameLine();
		}

		//Add Font Group
		CreateAddFontNode();

		ImGui::EndChild();

		//Attributes
		ImGui::NextColumn();

		CreateFontFamilySettingsPanel();

		ImGui::Columns(1);
		ImGui::PopID();
		ImGui::PopStyleColor();
	}

	void FontEditorCustomizationDetails::BeginNode(const std::string& id)
	{
		ImGui::PushID(id.c_str());
		ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(.6f, .6f, .6f, 1.0f));
		ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 2.0f);
		ImGui::BeginChild(id.c_str(), ImVec2(175.0f, 175.0f), true);
	}

	void FontEditorCustomizationDetails::CreateFontNode(const std::string& name, FontAttributes& attributes)
	{
		BeginNode(name);
		FontNode(name, attributes);
		EndNode();
	}

	void FontEditorCustomizationDetails::EndNode()
	{
		ImGui::EndChild();
		ImGui::PopStyleColor();
		ImGui::PopStyleVar();
		ImGui::PopID();
	}

	void FontEditorCustomizationDetails::CreateAddFontNode()
	{
		BeginNode("Add Font");
		ImVec2 windowSize = ImGui::GetWindowSize();
		ImVec2 buttonPos = ImVec2(windowSize.x / 2.0f, windowSize.y / 2.0f);
		const char* text = "Add Font";
		ImVec2 textSize = ImGui::CalcTextSize(text);
		ImVec2 textPos = ImVec2((windowSize.x / 2.0f) - (textSize.x / 3.0f), (windowSize.y / 2.0f) + (textSize.y + 5.0f));
		ImGui::SetCursorPos(buttonPos);
		if (detailsBuilderPtr->Button("+", FVector2(20.0f, 20.0f)))
		{
			fontFamily->AddFontToFamily("None", "");
		}
		ImGui::SetCursorPos(textPos);
		ImGui::Text(text);
		EndNode();
	}

	void FontEditorCustomizationDetails::FontNode(const std::string& name, FontAttributes& attributes)
	{
		ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(0, 0, 0, 0));
		detailsBuilderPtr->Property("", attributes.m_Name);
		ImGui::PopStyleColor();
		detailsBuilderPtr->Property(name.c_str(), attributes.m_Font);
		ImGui::SameLine();
		std::string file = "";
		auto texture = AssetManager::Get<Texture2D>("folder");
		if (ImGui::ImageButton((void*)*texture, ImVec2(20.0f, 20.0f), ImVec2(0, 1), ImVec2(1, 0)))
		{
			file = FileDialog::OpenFile("Font\0*.ttf*\0").c_str();
		}

		if (!file.empty())
		{
			attributes.m_FilePath = WinPath(file.c_str());
			fontFamily->ReplaceFont(attributes.m_Name, attributes.m_FilePath);
		}
		ImVec2 windowSize = ImGui::GetWindowSize();
		ImVec2 buttonPos = ImVec2(windowSize.x / 2.0f, windowSize.y - (20.0f + 10.0f));
		ImGui::SetCursorPos(buttonPos);
		if (detailsBuilderPtr->Button("X", FVector2(20.0f, 20.0f)))
		{
			fontFamily->RemoveFromFamily(name);
		}
	}

	void FontEditorCustomizationDetails::CreateFontFamilySettingsPanel()
	{
		ImGui::BeginChild("Attributes", ImVec2(0, 0), true);
		ImGui::Text("Attributes");
		if (ImGui::DragFloat("", &fontFamily->m_Size, 1.0f, 0.1f, 360.0f))
		{
			fontFamily->Resize();
		}

		ImGui::EndChild();
	}
}