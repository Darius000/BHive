#pragma  once

#include "Core.h"
#include "BHive/Events/Event.h"
#include "BHive/Events/ApplicationEvent.h"
#include "BHive/Platforms/Windows/Window.h"
#include "BHive/Layers/LayerStack.h"
#include "BHive/ImGui/ImGuiLayer.h"
#include "BHive/Assets/BResourceManager.h"
#include "BHive/Renderer/Shader/Shader.h"

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
		std::unique_ptr<BResourceManager> m_ResourceManager;
		std::unique_ptr<Shader> m_Shader;

		ImGuiLayer* m_ImGuiLayer;

		bool m_Running = true;
		LayerStack m_LayerStack;
	private:
		static Application* s_Instance;
	};

	//defined in client
	Application* CreateApplication();
}
