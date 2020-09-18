#include "Editor.h"
#include "EditorStack.h"

namespace BHive
{ 
	ImGuiPanel::ImGuiPanel(const char* label)
		:m_Label(label)
	{
		EditorStack::OpenEditor(Ref<ImGuiPanel>(this));
	}

	ImGuiPanel::~ImGuiPanel()
	{
		std::cout << "destroyed " << m_Label << "!\n";
	}
}
