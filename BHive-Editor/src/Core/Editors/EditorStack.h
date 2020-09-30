#pragma once

#include "BHive.h"
#include "ImGuiPanel.h"

namespace BHive
{

	class EditorStack
	{
	public:
		using Editors = std::vector<ImGuiPanel*>;
		using Iterator = Editors::iterator;
	
		EditorStack();
		~EditorStack();

		void OpenPanel(ImGuiPanel* panel);
		void ClosePanel(ImGuiPanel* panel);
		void ClosePanel(const uint32& index);
		inline Iterator begin() { return m_Editors.begin(); }
		inline Iterator end() { return m_Editors.end(); }
		inline size_t size(){ return m_Editors.size(); }
		inline ImGuiPanel* operator[](const uint32& index)
		{
			return m_Editors[index];
		}

	private:
		Editors m_Editors;
	};
}