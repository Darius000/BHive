#pragma once

#include "imgui.h"

namespace BHive
{
	class BHive_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnAttach() override;
		void OnDetach() override;
		void OnImGuiRender() override;
		void OnEvent(Event& e) override; 

		void Begin();
		void End();

		void BlockEvents(bool block) { m_BlockEvents = block;}
	private:
		float m_Time = 0.0f;
		bool m_BlockEvents = true;
		Scope<ImGuiStyle> m_Style;
	};
}