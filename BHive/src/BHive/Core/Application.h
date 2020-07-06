#pragma  once

#include "BHive/Core/ApplicationEvent.h"
#include "BHive/Platforms/Windows/Window.h"
#include "BHive/Core/LayerStack.h"
#include "BHive/Layers/ImGuiLayer.h"
#include "BHive/Managers/AssetLoader.h"

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
		bool OnWindowResize(WindowResizeEvent& e);

		Scope<Window> m_Window;

		LayerStack m_LayerStack;
		ImGuiLayer* m_ImGuiLayer;
		Scope<Time> m_Time;

		bool m_Minimized = false;
		bool m_Running = true;

		//Asset Loader
		Scope<AssetLoader> m_ApplicationAssetLoader;

	private:
		static Application* s_Instance;

		void LoadAssets();
	};

	//defined in client
	Application* CreateApplication();
}
