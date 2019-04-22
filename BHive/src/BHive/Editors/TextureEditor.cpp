#include "BHivePCH.h"
#include "TextureEditor.h"
#include "Assets/Asset.h"
#include "Assets/Texture2D.h"

namespace BHive
{

	TextureEditor::TextureEditor(Asset& asset, String editorName)
		:AssetEditor(asset, editorName)
	{

	}

	void TextureEditor::OnImGuiRender()
	{
		AssetEditor::OnImGuiRender();

		Texture2D* tex = dynamic_cast<Texture2D*>(m_Asset);
		float childSize = ImGui::GetWindowContentRegionWidth() / 2.0f;

		//Column1->Image displayed
		ImGui::BeginChild("Image", ImVec2(childSize, childSize), true);
		

		ImGui::Image((void*)(intptr_t)(m_Asset->GetData()), ImVec2(200.0f - 10.0f, 200.0f - 10.0f), ImVec2(0.0f, 1.0f), ImVec2(1.0f, 0.0f),ImVec4(1.0f, 1.0f, 1.0f, 1.0f), ImVec4(tex->BorderColor.r, tex->BorderColor.g, tex->BorderColor.b, 1.0f));
		ImGui::EndChild();

		ImGui::SameLine(ImGui::GetWindowContentRegionWidth() / 2.0f);

		//Column2->Settings
		ImGui::BeginChild("Settings", ImVec2(childSize, childSize), true);

		//Options
		ImGui::SetColorEditOptions(ImGuiColorEditFlags_::ImGuiColorEditFlags_PickerHueWheel);
		if (ImGui::ColorEdit3("Border Color", &tex->BorderColor.r) 
			|| ImGui::SliderInt("Wrapping", &tex->Wrapping, 0, 3))
		{
			
		}

		ImGui::EndChild();
	}

}