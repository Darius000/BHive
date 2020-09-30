#include "ImGuiPanel.h"

namespace BHive
{
	ImGuiPanel::ImGuiPanel(const std::string& label, ImGuiWindowFlags flags, bool runtimecreated)
		:m_Label(label), m_Flags(flags), m_RuntimeCreated(runtimecreated)
	{
		
	}

	ImGuiPanel::~ImGuiPanel()
	{

	}

	void ImGuiPanel::OnBeginWindow()
	{
		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_TabRounding, 0.0f);
		if(m_RuntimeCreated) 
		{	
			ImGui::SetNextWindowSize(ImVec2(500, 500), ImGuiCond_Once);
			m_Flags = m_Flags | ImGuiWindowFlags_NoSavedSettings;
		}

		ImGui::Begin(m_Label.c_str(), &m_isOpen, m_Flags | ImGuiWindowFlags_NoScrollbar);
	}

	void ImGuiPanel::OnRender()
	{
		OnBeginWindow();
		OnRenderWindow();
		OnEndWindow();
	}

	void ImGuiPanel::OnEndWindow()
	{
		ImGui::PopStyleVar(2);
		ImGui::End();	
	}
}