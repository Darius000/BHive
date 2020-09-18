#include "TextureEditor.h"

#include <imgui/imgui.h>

namespace BHive
{
	void TextureEditor::OnImGuiRender()
	{
		if (!m_Asset) { m_isOpen = false; return;}

		ImGui::Begin(m_Label, &m_isOpen, ImGuiWindowFlags_MenuBar);

		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("File##TextureEditor"))
			{
				if (ImGui::MenuItem("Exit##TextureEditor")) { m_isOpen = false; }
				if (ImGui::BeginMenu("Save##TextureEditor")) {}
				ImGui::EndMenu();
			}

			ImGui::EndMenuBar();
		}

		float ImageSize = ImGui::GetContentRegionAvailWidth() / 2.0f;
		ImGui::Columns(2, "Columns");
		uint32 ID = m_Asset->GetRendererID();
		ImGui::Image((void*)ID, ImVec2(ImageSize, ImageSize), ImVec2(0, 1), ImVec2(1, 0));
		ImGui::NextColumn();
		static int tilingMethodItem = 0;
		static int colorMinMethodItem = 0;
		static int colorMagMethodItem = 0;
		if (ImGui::Combo("Tiling Method##TextureEditor", &tilingMethodItem, s_TilingMethods))
		{
			m_Asset->m_TilingMethod = (TilingMethod)tilingMethodItem;
			m_Asset->InValidate();
		}

		if (ImGui::Combo("Min-Filter Color Method##TextureEditor", &colorMinMethodItem, s_Min_ColorMethods))
		{
			m_Asset->m_MinFilterColorMethod = (MinColorMethod)colorMinMethodItem;
			m_Asset->InValidate();
		}

		if (ImGui::Combo("Mag-Filter Color Method##TextureEditor", &colorMagMethodItem, s_Mag_ColorMethods))
		{
			m_Asset->m_MagFilterColorMethod = (MagColorMethod)colorMagMethodItem;
			m_Asset->InValidate();
		}

		if (ImGui::ColorPicker4("Border Color", *m_Asset->m_BorderColor))
		{
			m_Asset->InValidate();
		}

		static char buffer[256] = "";
		ImGui::InputText("Serialize Path", buffer, IM_ARRAYSIZE(buffer));

		if (ImGui::Button("Serialize"))
		{
			m_Asset->Serialize(buffer);
		}

		ImGui::End();
	}
}