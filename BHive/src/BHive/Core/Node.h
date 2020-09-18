#pragma once

#include "imgui.h"
#include "BHive/Core/PlatformDataTypes.h"
#include "BHive/ImGui/ImGuiWrappers.h"

namespace BHive
{
	template<typename T>
	class DoublyLinkedList;

	template<typename T>
	struct NodeItem;

	template<typename T>
	struct NodeLink;

	struct NodeGraphEditor;

	template<typename T>
	struct Node
	{
		Node() {}
		Node(const T& data) :m_Data(data) {}
		Node(const T& data, Node<T>* next)
			:m_Data(data), m_Next(next) {}
		Node(const T& data, Node<T>* next, Node<T>* previous)
			:m_Data(data), m_Next(next), m_Previous(previous) {}
		virtual ~Node() = default;

		void AddNextLink(Node<T>* Next)
		{
			if(m_OutputLinks.size() >= m_NumOutputs)
				return;

			NodeLink<T>* Link = new NodeLink<T>();
			Link->m_Next = Next;
			Link->m_Previous = this;
			m_OutputLinks.push_back(Link);
			Next->m_InputLinks.push_back(Link);
		}

		void AddPreviousLink(Node<T>* Previous)
		{
			if (m_InputLinks.size() >= m_NumInputs)
				return;

			NodeLink<T>* Link = new NodeLink<T>();
			Link->m_Next = this;
			Link->m_Previous = Previous;
			m_InputLinks.push_back(Link);
			Previous->m_OutputLinks.push_back(Link);
		}

		bool HasOutputLinks() const
		{
			return m_OutputLinks.size() > 0;
		}

		bool HasInputLinks() const
		{
			return m_InputLinks.size() > 0;
		}

		//Node<T>* m_Next = nullptr;
		//Node<T>* m_Previous = nullptr;
		int m_ID = 0;
		ImVec2 m_Size = ImVec2(120.0f, 50.0f);
		ImVec2 m_Position = ImVec2(0.0f, 0.0f);
		ImVec2 m_Offset = ImVec2(0.0f, 0.0f);
		ImColor m_Color = ImColor(150, 150, 150, 255);
		int m_NumInputs = 1;
		int m_NumOutputs = 1;
		T m_Data;
		std::vector<NodeLink<T>*> m_InputLinks;
		std::vector<NodeLink<T>*> m_OutputLinks;

		ImVec2 GetInputSlotPos(int slot) const
		{
			return ImVec2(m_Position.x, m_Position.y + m_Size.y * ((float)slot + 1) / ((float)m_NumInputs + 1));
		}
		ImVec2 GetOutputSlotPos(int slot) const
		{
			return ImVec2(m_Position.x + m_Size.x, m_Position.y + m_Size.y * ((float)slot + 1) / ((float)m_NumOutputs + 1));
		}

		virtual void OnImGuiRender()
		{

		}
	};

	template<typename T>
	struct NodeLink
	{
		NodeLink() = default;
		Node<T>* m_Previous = nullptr;
		Node<T>* m_Next = nullptr;
	};

	template<typename T>
	class DoublyLinkedList
	{
	public:
		DoublyLinkedList() = default;
		~DoublyLinkedList()
		{
			for (auto node : m_CreatedNodes)
			{
				delete node;
			}

			for (auto node : m_NodeItems)
			{
				delete node;
			}
		};

		Node<T>* GoBack(size_t Index)
		{
			if (!m_CurrentNode->HasInputLinks()) return m_CurrentNode;

			if (m_CurrentNode->m_InputLinks[Index]->m_Previous != nullptr)
				m_CurrentNode = m_CurrentNode->m_InputLinks[Index]->m_Previous;
			return m_CurrentNode;
		}

		Node<T>* GoForward(size_t Index)
		{
			if(!m_CurrentNode->HasOutputLinks()) return m_CurrentNode;

			if (m_CurrentNode->m_OutputLinks[Index]->m_Next != nullptr)
				m_CurrentNode = m_CurrentNode->m_OutputLinks[Index]->m_Next;
			return m_CurrentNode;
		}

		void Insert(Node<T>* node)
		{
			auto newNode = node;
			newNode->m_ID = ++m_CurrentID;
			m_CreatedNodes.push_back(newNode);
			m_NodeItems.push_back(new NodeItem<T>("node", node, &m_NodeGraph));
			//auto comment = new CommentNode("This is a comment");
			//new NodeItem<std::string>("commentNodeItem", comment, &m_NodeGraph);

			if (m_Head == nullptr)
			{
				m_Head = newNode;
				m_CurrentNode = m_Head;
				m_Tail = m_Head;
				return;
			}

			m_CurrentNode->AddNextLink(newNode);
			//m_CurrentNode->m_Next = newNode;
			m_CurrentNode = newNode;
			m_Tail = m_CurrentNode;
		}

		
		void OnImGuiRender()
		{
			
			m_NodeGraph.Begin();
			
			for (auto node : m_NodeItems)
			{
				node->Draw();
			}
		
			m_NodeGraph.End();
		}

		NodeGraphEditor m_NodeGraph;
		Node<T>* m_Head = nullptr;
		Node<T>* m_Tail = nullptr;
		Node<T>* m_CurrentNode = nullptr;
		std::vector<Node<T>*> m_CreatedNodes;
		std::vector<NodeItem<T>*> m_NodeItems;
		int m_CurrentID = -1;
	};
}