#include "BHivePCH.h"
#include "TextureEditorLayer.h"

namespace BHive
{

	TextureEditorLayer::TextureEditorLayer()
		:Layer("Texture Editor")
	{

	}

	Ref<Texture2D> TextureEditorLayer::TextureToEdit;

	void TextureEditorLayer::OnImGuiRender()
	{
		if(m_ShowEditor) DisplayTextureEditor();
	}

	void TextureEditorLayer::ShowEditor(Ref<Texture2D> texture)
	{
		TextureToEdit = texture;
		m_ShowEditor = true;
	}

	void TextureEditorLayer::CloseEditor()
	{
		m_ShowEditor = false;
	}

	void TextureEditorLayer::DisplayTextureEditor()
	{
		if(!TextureToEdit) return;

		ImGui::Begin(*TextureToEdit->GetName(), &m_ShowEditor, ImGuiWindowFlags_MenuBar);

		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("File##TextureEditor"))
			{
				if (ImGui::MenuItem("Exit##TextureEditor")) { m_ShowEditor = false; }
				if (ImGui::BeginMenu("Save##TextureEditor")) {}
				ImGui::EndMenu();
			}

			ImGui::EndMenuBar();
		}

		float ImageSize = ImGui::GetContentRegionAvailWidth() / 2.0f;
		ImGui::Columns(2, "Columns");
		uint32 ID = TextureToEdit->GetRendererID();
		ImGui::Image((void*)ID, ImVec2(ImageSize, ImageSize), ImVec2(0, 1), ImVec2(1, 0));
		ImGui::NextColumn();
		static int tilingMethodItem = 0;
		static int colorMinMethodItem = 0;
		static int colorMagMethodItem = 0;
		if (ImGui::Combo("Tiling Method##TextureEditor", &tilingMethodItem, s_TilingMethods))
		{
			TextureToEdit->m_TilingMethod = (TilingMethod)tilingMethodItem;
			TextureToEdit->InValidate();
		}

		if (ImGui::Combo("Min-Filter Color Method##TextureEditor", &colorMinMethodItem, s_Min_ColorMethods))
		{
			TextureToEdit->m_MinFilterColorMethod = (MinColorMethod)colorMinMethodItem;
			TextureToEdit->InValidate();
		}

		if (ImGui::Combo("Mag-Filter Color Method##TextureEditor", &colorMagMethodItem, s_Mag_ColorMethods))
		{
			TextureToEdit->m_MagFilterColorMethod = (MagColorMethod)colorMagMethodItem;
			TextureToEdit->InValidate();
		}

		if (ImGui::ColorPicker4("Border Color", *TextureToEdit->m_BorderColor))
		{
			TextureToEdit->InValidate();
		}

		static char buffer[256] = "";
		ImGui::InputText("Serialize Path", buffer, IM_ARRAYSIZE(buffer));

		if (ImGui::Button("Serialize"))
		{
			Texture::Serialize(TextureToEdit, buffer);
		}

		ImGui::End();
	}

	bool TextureEditorLayer::m_ShowEditor = false;

}