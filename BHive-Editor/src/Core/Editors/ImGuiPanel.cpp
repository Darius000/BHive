#include "ImGuiPanel.h"

namespace BHive
{
	ImGuiPanel::ImGuiPanel(const std::string& label, ImGuiWindowFlags flags, uint64 id, bool runtimecreated)
		:m_Label(label), m_Flags(flags), m_RuntimeCreated(runtimecreated), m_ID(id), m_WindowPadding(10.0f, 10.0f),
		m_FramePadding(5.0f, 5.0f)
	{
		
	}

	ImGuiPanel::~ImGuiPanel()
	{

	}

	void ImGuiPanel::OnBeginWindow()
	{
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, {m_WindowPadding.x, m_WindowPadding.y});
		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, {m_FramePadding.x, m_FramePadding.y});
		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_TabRounding, 0.0f);
		if(m_RuntimeCreated) 
		{	
			ImGui::SetNextWindowSize(ImVec2(700, 500), ImGuiCond_Once);
			m_Flags = m_Flags | ImGuiWindowFlags_NoSavedSettings;
		}

		ImGui::Begin(m_Label.c_str(), &m_IsOpen, m_Flags | ImGuiWindowFlags_NoScrollbar);
		ImGui::PushID((int)m_ID);

		//Check if window is focused and hovered
		b_IsFocused = ImGui::IsWindowFocused();
		b_IsHovered = ImGui::IsWindowHovered();	

		/*if (b_IsFocused)
		{
			OnFocused();
		}
		else
		{
			OnUnFocused();
		}*/
	}

	void ImGuiPanel::OnRender()
	{
		OnBeginWindow();
		if(ImGui::BeginMenuBar())
		{ 
			OnRenderMenuBar();

			ImGui::EndMenuBar();
		}
		OnRenderWindow();
		OnEndWindow();
	}

	void ImGuiPanel::OnEndWindow()
	{
		ImGui::PopStyleVar(4);
		ImGui::PopID();
		ImGui::End();	
	}

	bool OnScrolled(MouseScrolledEvent& e){ return true;}

	void ImGuiPanel::OnRecieveEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<MouseScrolledEvent>(this, &ImGuiPanel::OnMouseScrolled);
		dispatcher.Dispatch<MouseMovedEvent>(this, &ImGuiPanel::OnMouseMoved);
		dispatcher.Dispatch<MouseButtonPressedEvent>(this, &ImGuiPanel::OnMouseButtonPressed);
		dispatcher.Dispatch<MouseButtonReleasedEvent>(this, &ImGuiPanel::OnMouseButtonReleased);
		dispatcher.Dispatch<KeyPressedEvent>(this, &ImGuiPanel::OnKeyPressed);
		dispatcher.Dispatch<KeyReleasedEvent>(this, &ImGuiPanel::OnKeyReleased);
	}

	void ImGuiPanel::Close()
	{
		m_IsOpen = false;
	}

	bool ImGuiPanel::OnMouseScrolled(MouseScrolledEvent& e)
	{
		return false;
	}

	bool ImGuiPanel::OnMouseMoved(MouseMovedEvent& e)
	{
		return false;
	}

	bool ImGuiPanel::OnMouseButtonPressed(MouseButtonPressedEvent& e)
	{
		return false;
	}

	bool ImGuiPanel::OnMouseButtonReleased(MouseButtonReleasedEvent& e)
	{
		return false;
	}

	bool ImGuiPanel::OnKeyPressed(KeyPressedEvent& e)
	{
		return false;
	}

	bool ImGuiPanel::OnKeyReleased(KeyReleasedEvent& e)
	{
		return false;
	}

	void ImGuiPanel::OnFocused()
	{

	}

	void ImGuiPanel::OnUnFocused()
	{

	}

	bool ImGuiPanel::IsFocusedAndHoverd() const
	{
		return b_IsFocused && b_IsHovered;
	}

}