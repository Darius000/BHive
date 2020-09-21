#include "BHivePCH.h"
#include "Editor.h"
#include "BHive/Core/Registry/ClassRegistry.h"

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

		ClassRegistry::GetEditorForAsset(m_Asset->GetAssetType())->CreateCustomizedDetails(detailsBuilder, m_Asset);
	}
}
