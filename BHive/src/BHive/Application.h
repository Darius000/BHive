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
		void PopLayer(Layer* layer);
		void PopOverlay(Layer* layer);

		static inline Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }

	private:
		bool OnWindowClosed(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;

		bool m_Running = true;
		LayerStack m_LayerStack;
	private:
		static Application* s_Instance;
	};

	//defined in client
	Application* CreateApplication();
}

