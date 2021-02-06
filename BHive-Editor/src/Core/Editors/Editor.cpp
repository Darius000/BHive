#include "Editor.h"
#include "EditorClassRegistry.h"
#include "Editor.h"
#include "Serializer/Serialize.h"

namespace BHive
{ 

	Editor::Editor(const std::string& label, IAssetType* asset, uint64 id) 
		:ImGuiPanel(label, ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_AlwaysVerticalScrollbar, id, true), m_Asset(asset)
	{

	}

	void Editor::OnRenderMenuBar()
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Exit")) { Close(); }
			if (ImGui::MenuItem("Save"))
			{
				//Serialize(m_Asset, "Assets/" + m_Asset->m_Name);
			}

			ImGui::EndMenu();
		}

		auto editor = EditorClassRegistry::GetEditorForAsset(m_Asset->GetAssetTypeName());
		if(editor) editor->CreateMenuBar(detailsBuilder, m_Asset);
	}

	void Editor::OnRenderWindow()
	{	
		auto editor = EditorClassRegistry::GetEditorForAsset(m_Asset->GetAssetTypeName());
		if(editor) editor->CreateCustomizedDetails(detailsBuilder, m_Asset);
	}
}
