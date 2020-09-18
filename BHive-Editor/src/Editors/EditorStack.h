#pragma once

#include "BHive.h"
#include "Editor.h"

namespace BHive
{
	class ImGuiPanel;

	using Editors = std::vector<Ref<ImGuiPanel>>;

	class EditorStack
	{
	public:
		EditorStack();
		~EditorStack();

		static void OpenEditor(Ref<ImGuiPanel> editor);
		static void OnImGuiRender();
		static void OpenEditorForAsset(Asset* asset);

	private:
		static Editors m_Editors;
	};
}