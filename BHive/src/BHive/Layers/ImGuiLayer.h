#pragma once

#include "imgui.h"

namespace BHive
{
	class BHive_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();

	private:
		void ShowMenuItems();
		void ShowWindowItems();
		void ShowProfiler(bool* open = (bool*)nullptr);

	private:
		float m_Time = 0.0f;
		Scope<ImGuiStyle> m_Style;

	private:
		bool m_ShowStyleEditor = false;
		bool m_ShowDemoWindow = false;
		bool m_ShowProfiler = false;
	};
}