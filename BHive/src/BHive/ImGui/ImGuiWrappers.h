#pragma once

#include "imgui.h"
#include "BHive/Core/Node.h"
#include "BHive/Core/MouseCodes.h"



namespace BHive
{

	static inline ImVec2 operator+(const ImVec2& lhs, const ImVec2& rhs) { return ImVec2(lhs.x + rhs.x, lhs.y + rhs.y); }
	static inline ImVec2 operator-(const ImVec2& lhs, const ImVec2& rhs) { return ImVec2(lhs.x - rhs.x, lhs.y - rhs.y); }

	static inline ImColor operator*(const ImColor& lhs, float s) 
	{
		return ImColor(lhs.Value.x * s, lhs.Value.y * s, lhs.Value.z * s, lhs.Value.w * s);
	}

	struct NodeEditorSettings
	{
		const char* m_Title = "Node Editor";
		float m_NodeSlotRadius = 4.0f;
		ImColor m_InputColor = ImColor(150, 150, 0, 255);
		ImColor m_OutputColor = ImColor(150, 150, 150, 255);
		ImColor m_LinkColor = ImColor(200, 200, 100, 255);
		ImVec2	m_NodePadding = ImVec2(8.0f, 8.0f);
		ImColor m_GridColor = ImColor(200, 200, 200, 40);
		float m_GridSize = 64.0f;
		ImVec2 m_FramePadding = ImVec2(1,1);
		ImVec2 m_WindowPadding = ImVec2(0,0);
		ImColor m_ChildBackgroundColor = ImColor(0,0,0,255);
		float m_WindowRounding = 0.0f;
		float m_NodeRounding = 2.0f;
		bool m_CurvedLinks = true;
		float m_LinkThickness = 2.0f;
	};

	struct NodeGraphEditor
	{
		NodeGraphEditor() = default;

		void Begin()
		{
			if (m_ShowGraphSettings)
			{
				ShowGraphSettings(&m_ShowGraphSettings);
			}

			ImGui::SetNextWindowSize(ImVec2(700, 600), ImGuiCond_FirstUseEver);
			ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, m_Settings.m_FramePadding);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, m_Settings.m_WindowPadding);
			ImGui::PushStyleColor(ImGuiCol_ChildBg, (ImU32)m_Settings.m_ChildBackgroundColor);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, m_Settings.m_WindowRounding);

			ImGui::Begin(m_Settings.m_Title, (bool*)0, ImGuiWindowFlags_MenuBar);


			if (ImGui::BeginMenuBar())
			{
				if (ImGui::BeginMenu("Settings"))
				{
					if (ImGui::MenuItem("Style"))
					{
						m_ShowGraphSettings = true;
					}

					ImGui::EndMenu();
				}

				ImGui::EndMenuBar();
			}

			

			m_IO = &ImGui::GetIO();

			ImGui::BeginChild("scrolling_region", ImVec2(0, 0), true,
				ImGuiWindowFlags_NoScrollbar |
				ImGuiWindowFlags_NoMove);

			m_CurrentDrawList = ImGui::GetWindowDrawList();

			m_WindowPos = ImGui::GetCursorScreenPos();
			ImVec2 canvas_sz = ImGui::GetWindowSize();
			for (float x = fmodf(m_Scrolling.x, m_Settings.m_GridSize); x < canvas_sz.x; x += m_Settings.m_GridSize)
				m_CurrentDrawList->AddLine(ImVec2(x, 0.0f) + m_WindowPos, ImVec2(x, canvas_sz.y) + m_WindowPos, (ImU32)m_Settings.m_GridColor);
			for (float y = fmodf(m_Scrolling.y, m_Settings.m_GridSize); y < canvas_sz.y; y += m_Settings.m_GridSize)
				m_CurrentDrawList->AddLine(ImVec2(0.0f, y) + m_WindowPos, ImVec2(canvas_sz.x, y) + m_WindowPos, (ImU32)m_Settings.m_GridColor);
		}

		void End()
		{
			if (ImGui::IsWindowHovered() && !ImGui::IsAnyItemActive() && ImGui::IsMouseDragging((int)MouseButton::Middle, 0.0f))
				m_Scrolling = m_Scrolling + m_IO->MouseDelta;


			ImGui::EndChild();

			ImGui::PopStyleVar();
			ImGui::PopStyleVar();
			ImGui::PopStyleColor();
			ImGui::PopStyleVar();

			ImGui::End();
		}

		void ShowGraphSettings(bool* IsOpen)
		{
			ImGui::Begin("Settings", IsOpen, ImGuiWindowFlags_AlwaysAutoResize);
			ImGui::DragFloat("Node Slot Radius", &m_Settings.m_NodeSlotRadius, 1.0f, 4.0f, 7.0f);
			ImGui::ColorEdit4("Input Slot Color", (float*)&m_Settings.m_InputColor);
			ImGui::ColorEdit4("Output Slot Color", (float*)&m_Settings.m_OutputColor);
			ImGui::ColorEdit4("Node Link Color", (float*)&m_Settings.m_LinkColor);
			ImGui::ColorEdit4("Grid Color", (float*)&m_Settings.m_GridColor);
			ImGui::ColorEdit4("Background Color", (float*)&m_Settings.m_ChildBackgroundColor);
			ImGui::DragFloat("Grid Size", &m_Settings.m_GridSize, 1.0f, 30.0f, 64.0f);
			ImGui::DragFloat("Window Rounding", &m_Settings.m_WindowRounding, 1.0f, 0.0f, 7.0f);
			ImGui::DragFloat("Node Rounding", &m_Settings.m_NodeRounding, 1.0f, 0.0f, 7.0f);
			ImGui::DragFloat2("Node Padding", (float*)&m_Settings.m_NodePadding);
			ImGui::Checkbox("Curved Links", &m_Settings.m_CurvedLinks);
			ImGui::DragFloat("Link Thickness", &m_Settings.m_LinkThickness);
			ImGui::End();
		}

		ImVec2 m_Scrolling = ImVec2(0.0f, 0.0f);
		int	m_NodesHoveredInListID = -1;
		int	m_NodeHoveredID = -1;
		int m_SelectedNodeID = -1;
		bool m_IsAnyNodesActive = false;
		bool m_IsNodesActive = false;
		ImDrawList* m_CurrentDrawList = nullptr;
		ImGuiIO* m_IO = nullptr;
		ImVec2 m_WindowPos;

		NodeEditorSettings m_Settings;
		bool m_ShowGraphSettings = false;
	};

	template<typename T>
	struct NodeItem
	{
		NodeItem() = default;
		NodeItem(const char* Label, BHive::Node<T>* inNode, NodeGraphEditor* GraphEditor)
			:  m_Title(Label), m_Node(inNode), m_GraphEditor(GraphEditor)
		{
			
		}
		
		void Draw()
		{
			m_CurrentDrawList = ImGui::GetWindowDrawList();

			ImGui::SameLine();
			ImGui::PushID(m_Node->m_ID);
			m_CurrentDrawList->ChannelsSplit(3);

			m_Node->m_Offset = m_GraphEditor->m_WindowPos + m_Node->m_Position + m_GraphEditor->m_Scrolling;
			m_NodeMin = m_Node->m_Offset + m_Node->m_Position;

			m_CurrentDrawList->ChannelsSetCurrent(1);

			ImGui::SetCursorScreenPos(m_NodeMin + m_GraphEditor->m_Settings.m_NodePadding);
			ImGui::BeginGroup();

			m_Node->OnImGuiRender();

			ImGui::EndGroup();

			m_GraphEditor->m_IsAnyNodesActive = ImGui::IsAnyItemActive();
			m_GraphEditor->m_IsNodesActive = (!m_GraphEditor->m_IsAnyNodesActive && ImGui::IsAnyItemActive());
			m_Node->m_Size = ImGui::GetItemRectSize() + m_GraphEditor->m_Settings.m_NodePadding + m_GraphEditor->m_Settings.m_NodePadding;
			m_RectMax = m_NodeMin + m_Node->m_Size;

			m_CurrentDrawList->ChannelsSetCurrent(2);

			/*for (int link_idx = 0; link_idx < links.Size; link_idx++)
			{
				NodeLink* link = &links[link_idx];
				Node* node_inp = &nodes[link->InputIdx];
				Node* node_out = &nodes[link->OutputIdx];
				ImVec2 p1 = offset + node_inp->GetOutputSlotPos(link->InputSlot);
				ImVec2 p2 = offset + node_out->GetInputSlotPos(link->OutputSlot);
				draw_list->AddBezierCurve(p1, p1 + ImVec2(+50, 0), p2 + ImVec2(-50, 0), p2, IM_COL32(200, 200, 100, 255), 3.0f);
			}*/

			for (auto link : m_Node->m_OutputLinks)
			{
				ImVec2 p1 = link->m_Previous->m_Offset + link->m_Previous->GetOutputSlotPos(0);
				ImVec2 p2 = link->m_Next->m_Offset + link->m_Next->GetInputSlotPos(0);

				m_GraphEditor->m_Settings.m_CurvedLinks ?
					m_CurrentDrawList->AddBezierCurve(p1, p1 + ImVec2(+50, 0), p2 + ImVec2(-50, 0), p2, (ImU32)m_GraphEditor->m_Settings.m_LinkColor, m_GraphEditor->m_Settings.m_LinkThickness) :
					m_CurrentDrawList->AddLine(p1, p2, (ImU32)m_GraphEditor->m_Settings.m_LinkColor, m_GraphEditor->m_Settings.m_LinkThickness);
			}

			m_CurrentDrawList->ChannelsSetCurrent(0);
			ImGui::SetCursorScreenPos(m_NodeMin);

			ImGui::InvisibleButton(std::to_string(m_Node->m_ID).c_str(), m_Node->m_Size);
			if (ImGui::IsItemHovered())
			{
				m_GraphEditor->m_NodeHoveredID = m_Node->m_ID;
			}

			m_IsActive = ImGui::IsItemActive();
			if (m_GraphEditor->m_IsNodesActive || m_IsActive)
				m_GraphEditor->m_SelectedNodeID = m_Node->m_ID;
			if (m_IsActive && ImGui::IsMouseDragging((int)BHive::MouseButton::Left))
			{
				m_Node->m_Position = m_Node->m_Position + m_GraphEditor->m_IO->MouseDelta;
			}

			ImU32 node_bg_color = (m_GraphEditor->m_NodesHoveredInListID == m_Node->m_ID ||
				m_GraphEditor->m_NodeHoveredID == m_Node->m_ID ||
				(m_GraphEditor->m_NodesHoveredInListID == -1 &&
					m_GraphEditor->m_SelectedNodeID == m_Node->m_ID)) ?
				(ImU32)(m_Node->m_Color * .5f): (ImU32)m_Node->m_Color;

			m_CurrentDrawList->AddRectFilled(m_NodeMin, m_RectMax, node_bg_color, m_GraphEditor->m_Settings.m_NodeRounding);
			m_CurrentDrawList->AddRect(m_NodeMin, m_RectMax, IM_COL32(100, 100, 100, 255), m_GraphEditor->m_Settings.m_NodeRounding);
			for (int slot_idx = 0; slot_idx < m_Node->m_NumInputs; slot_idx++)
				m_CurrentDrawList->AddCircleFilled(m_Node->m_Offset + m_Node->GetInputSlotPos(slot_idx), m_GraphEditor->m_Settings.m_NodeSlotRadius, (ImU32)m_GraphEditor->m_Settings.m_InputColor);
			for (int slot_idx = 0; slot_idx < m_Node->m_NumOutputs; slot_idx++)
				m_CurrentDrawList->AddCircleFilled(m_Node->m_Offset + m_Node->GetOutputSlotPos(slot_idx), m_GraphEditor->m_Settings.m_NodeSlotRadius, (ImU32)m_GraphEditor->m_Settings.m_OutputColor);

			m_CurrentDrawList->ChannelsMerge();

			ImGui::PopID();
		}
		
		const char* m_Title;
		ImVec2 m_NodeMin = ImVec2(0,0);
		ImVec2 m_RectMax = ImVec2(0,0);
		ImDrawList* m_CurrentDrawList = nullptr;
		bool m_IsActive = false;
		BHive::Node<T>* m_Node = nullptr;
		NodeGraphEditor* m_GraphEditor = nullptr;

	};

	
}
