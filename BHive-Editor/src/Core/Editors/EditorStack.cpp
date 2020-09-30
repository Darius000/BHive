#include "EditorStack.h"

namespace BHive
{
	EditorStack::EditorStack()
	{
		
	}

	EditorStack::~EditorStack()
	{
		for (auto& editor : m_Editors)
		{
			delete editor;
		}
	}

	void EditorStack::OpenPanel(ImGuiPanel* editor)
	{
		m_Editors.push_back(editor);
	}

	void EditorStack::ClosePanel(ImGuiPanel* panel)
	{
		auto it = std::find(m_Editors.begin(), m_Editors.end(), panel);
		if (it != m_Editors.end())
		{
			m_Editors.erase(it);
		}
	}

	void EditorStack::ClosePanel(const uint32& index)
	{
		ClosePanel(m_Editors[index]);
	}
}