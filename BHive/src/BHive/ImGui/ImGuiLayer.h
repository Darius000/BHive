#pragma once

#include "BHive/Layers/Layer.h"
#include "BHive/Events/MouseEvent.h"
#include "BHive/Events/KeyEvent.h"
#include "BHive/Events/ApplicationEvent.h"


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
		float m_Time = 0.0f;
	};
}