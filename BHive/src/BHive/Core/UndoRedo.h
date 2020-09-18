#pragma once


#include "Node.h"
#include "BHive/ImGui/ImGuiWrappers.h"

namespace BHive
{
	struct FileHistoryNode : public Node<WinPath>
	{
		FileHistoryNode(const WinPath& data)
		{
			m_Data = data;
			m_Color = IM_COL32(255, 100, 0, 150);
			m_NumInputs = 1;
			m_NumOutputs = 1;
		}

		void OnImGuiRender() override
		{		
			ImGui::TextDisabled("Directory %s" ,*m_Data);
		}
	};

	struct CommentNode : public Node<std::string>
	{
		CommentNode(const std::string& data)
		{
			m_Data = data;
			m_Color = IM_COL32(255, 255, 255, 150);
			m_NumInputs = 0;
			m_NumOutputs = 0;
		}

		void OnImGuiRender() override
		{
			ImGui::InputTextMultiline("Comment", (char*)m_Data.c_str(), m_Data.capacity());
		}
	};

	template<typename T>
	class IUndoRedo
	{
	public:
		IUndoRedo()
		{
			m_History.m_NodeGraph.m_Settings.m_Title = "File Browser History";
		}

		Node<T>* Undo()
		{
			return m_History.GoBack(0);
		}

		Node<T>* Redo()
		{
			return m_History.GoForward(0);
		}

		void ClearHistory()
		{
			m_History.Clear();
		}

		void InsertHistory(Node<T>* node)
		{
			m_History.Insert(node);
		}

		DoublyLinkedList<T> m_History;
	};
}