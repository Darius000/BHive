#include "Editor.h"
#include "EditorClassRegistry.h"
#include "Editor.h"

namespace BHive
{ 

	void Editor::OnRenderWindow()
	{
		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("Exit")) { m_isOpen = false; }
				if (ImGui::MenuItem("Save")) {}
				ImGui::EndMenu();
			}

			ImGui::EndMenuBar();
		}

		auto editor = EditorClassRegistry::GetEditorForAsset(m_Asset->GetAssetType());
		if(editor) editor->CreateCustomizedDetails(detailsBuilder, m_Asset);
	}
}
