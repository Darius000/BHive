#include "BHivePCH.h"
#include "EditorRenderLayer.h"
#include "Editors/AssetEditor.h"

namespace BHive
{

	void EditorRenderLayer::OnAttach()
	{
		BH_INFO("Rendering Editors");
	}

	void EditorRenderLayer::OnImGuiRender()
	{
		for (auto& editor : AssetEditor::s_AssetEditors)
		{
			editor->ImGuiRender();
		}
	}

}