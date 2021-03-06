#pragma once

#include "BHive.h"
#include "imgui.h"

namespace BHive
{

	class ImGuiPanel
	{
	public:
		ImGuiPanel() = default;
		ImGuiPanel(const std::string& label, ImGuiWindowFlags flags, uint64 id = 0 ,bool runtimecreated  = false);
		virtual ~ImGuiPanel();

		void OnBeginWindow();
		virtual void OnRenderMenuBar() = 0;
		virtual	void OnRenderWindow() = 0;
		void OnRender();
		void OnEndWindow();

		//Receive events
		void OnRecieveEvent(Event& event);

		void Close();

		virtual bool OnMouseScrolled(MouseScrolledEvent& e);
		virtual bool OnMouseMoved(MouseMovedEvent& e);
		virtual bool OnMouseButtonPressed(MouseButtonPressedEvent& e);
		virtual bool OnMouseButtonReleased(MouseButtonReleasedEvent& e);
		virtual bool OnKeyPressed(KeyPressedEvent& e);
		virtual bool OnKeyReleased(KeyReleasedEvent& e);

		inline bool IsOpen() const { return m_IsOpen; }

		virtual void OnFocused();
		virtual void OnUnFocused();
		bool IsFocusedAndHoverd() const;

	protected:
		FVector2 m_WindowPadding;
		FVector2 m_FramePadding;

	private:
		bool m_IsOpen = true;

		std::string m_Label;

		ImGuiWindowFlags m_Flags = 0;

		bool m_RuntimeCreated = false;

		bool b_IsFocused = false;
		
		bool b_IsHovered = false;

		uint64 m_ID;
	};
}