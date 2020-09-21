#pragma once

#include "ImGuiPanel.h"

namespace BHive
{

	using Editors = std::vector<Scope<ImGuiPanel>>;

	class EditorStack
	{
	public:
		EditorStack();
		~EditorStack();

		static void OpenEditor(ImGuiPanel* editor);
		static void OnImGuiRender();

	private:
		static Editors m_Editors;
	};
}