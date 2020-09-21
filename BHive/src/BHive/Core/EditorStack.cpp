#include "BHivePCH.h"
#include "EditorStack.h"

namespace BHive
{

	EditorStack::EditorStack()
	{
		
	}

	EditorStack::~EditorStack()
	{
		
	}

	void EditorStack::OpenEditor(ImGuiPanel* editor)
	{
		m_Editors.emplace_back(editor);
	}

	void EditorStack::OnImGuiRender()
	{
		for (int i = 0; i < m_Editors.size(); i++)
		{
			m_Editors[i]->OnRender();

			if(!m_Editors[i]->m_isOpen)
			{
				auto it = std::find(m_Editors.begin(), m_Editors.end(), m_Editors[i]);
				m_Editors.erase(it);
			}

			
		}
	}

	Editors EditorStack::m_Editors;
}