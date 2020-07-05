#include "BHivePCH.h"
#include "Application.h"

#include "BHive/Core/Log.h"
#include "BHive/Renderer/RendererAPI.h"
#include "BHive/Renderer/Renderer.h"
#include "BHive/Renderer/RenderCommands.h"
#include "BHive/Core/Input.h"
#include "BHive/Object/ActorManager.h"
#include "BHive/Object/Object.h"
#include "BHive/Renderer/Shader.h"
#include "BHive/Managers/AssetLoader.h"
#include "BHive/Managers/AssetManagers.h"

namespace BHive
{
	Application* Application::s_Instance = nullptr;

	Application::Application()
	{

		BH_CORE_ASSERT(!s_Instance, "Application Already Exists!");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_ONE_PARAM(Application::OnEvent));

		{
			BH_PROFILE_SCOPE("Load Engine Assets");
			WinPath EngineAssetFolder("..\\BHive\\Assets");
			WinPath SandBoxAssetFolder("..\\Sandbox\\Assets");
			Ref<AssetLoader> EngineAssetLoader = Make_Ref<AssetLoader>(EngineAssetFolder);
			Ref<AssetLoader> SandBoxAssetLoader = Make_Ref<AssetLoader>(SandBoxAssetFolder);
		}

		Ref<Texture2D> m_WindowsIcon = TextureManager::Get("folder");
		m_Window->SetIcon(m_WindowsIcon);
		//m_Window->SetVSync(false);

		Renderer::Init();

		m_Time = Make_Scope<WindowsTime>();
		m_ImGuiLayer = new ImGuiLayer();

		PushOverlay(m_ImGuiLayer);
	}


	Application::~Application()
	{
		
	}
	
	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_ONE_PARAM(Application::OnWindowClosed));
		dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_ONE_PARAM(Application::OnWindowResize));

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{
			(*--it)->OnEvent(e);
			if (e.m_Handled)
			{
				break;
			}
		}
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}

	void Application::PopLayer(Layer * layer)
	{
		m_LayerStack.PopLayer(layer);
		layer->OnDetach();
	}

	void Application::PopOverlay(Layer* layer)
	{
		m_LayerStack.PopOverlay(layer);
		layer->OnDetach();
	}

	void Application::Run()
	{
		BH_PROFILE_FUNCTION();
			
		ActorManager::Start();

		while (m_Running)
		{
			m_Time->Update();

			if (!m_Minimized)
			{
				for (Layer* layer : m_LayerStack)
				{
					layer->OnUpdate(*m_Time);
				}

				ActorManager::Update(*m_Time);
			}

			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
			{
				layer->OnImGuiRender();
			}
			m_ImGuiLayer->End();

			m_Window->OnUpdate();

			ObjectManager::CheckPendingDestroy();
		}
	}

	bool Application::OnWindowClosed(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		if (e.GetWidth() == 0 || e.GetHeight() == 0)
		{
			m_Minimized = true;
			return false;
		}

		m_Minimized = false;

		Renderer::OnWindowResized(e.GetWidth(), e.GetHeight());

		return false;
	}
}
