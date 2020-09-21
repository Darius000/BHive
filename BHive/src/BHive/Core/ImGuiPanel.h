#pragma once

#include "imgui.h"

namespace BHive
{
	class ImGuiPanel
	{
	public:
		ImGuiPanel() = default;
		ImGuiPanel(const std::string& label, ImGuiWindowFlags flags);
		virtual ~ImGuiPanel();

		void OnBeginWindow();
		virtual	void OnRenderWindow() = 0;
		void OnRender();
		void OnEndWindow();

		bool m_isOpen = true;
		std::string m_Label;
		ImGuiWindowFlags m_Flags = 0;
	};
}