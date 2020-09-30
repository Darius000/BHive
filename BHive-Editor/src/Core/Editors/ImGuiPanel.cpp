#include "ImGuiPanel.h"

namespace BHive
{
	ImGuiPanel::ImGuiPanel(const std::string& label, ImGuiWindowFlags flags)
		:m_Label(label), m_Flags(flags)
	{
		
	}

	ImGuiPanel::~ImGuiPanel()
	{

	}

	void ImGuiPanel::OnBeginWindow()
	{
		ImGui::Begin(m_Label.c_str(), &m_isOpen, m_Flags);

	}

	void ImGuiPanel::OnRender()
	{
		OnBeginWindow();
		OnRenderWindow();
		OnEndWindow();
	}

	void ImGuiPanel::OnEndWindow()
	{
		ImGui::End();
	}
}