#pragma once

#include "Core.h"
#include "Events/Event.h"
#include "BHive/Events/ApplicationEvent.h"
#include "BHive/Window.h"
#include "BHive/LayerStack.h"

namespace BHive
{
	class BHive_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

	private:
		bool OnWindowClosed(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;

		bool m_Running = true;
		LayerStack m_LayerStack;
	};

	//defined in client
	Application* CreateApplication();
}

