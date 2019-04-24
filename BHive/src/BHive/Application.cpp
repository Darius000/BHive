#include "BHivePCH.h"
#include "Application.h"

#include "BHive/Log.h"

#include <glad/glad.h>

#include "Input.h"
#include "BHive/EditorTime.h"
#include "Layers/EditorRenderLayer.h"
#include "Layers/RenderLayer.h"
#include "BResourceManager.h"
#include "Layers/AssetManagerLayer.h"

namespace BHive
{
	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		BH_CORE_ASSERT(!s_Instance, "Application Already Exists!");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BH_BIND_EVENT_FN(&Application::OnEvent));

		m_ResourceManager = std::make_unique<BResourceManager>();
		m_ResourceManager->Create("Resources\\Engine", "Content");

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

		PushLayer(new RenderLayer());

		PushLayer(new AssetManagerLayer(*m_ResourceManager.get()));

		PushLayer(new EditorRenderLayer());
	}


	Application::~Application()
	{
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BH_BIND_EVENT_FN(&Application::OnWindowClosed));

		//BH_CORE_TRACE("{0}", e.ToString());

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
		while (m_Running)
		{
			glClearColor(.5f, .5f, .5f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			Time::Update();

			//BH_CORE_TRACE("{0},{1}", Time::GetTime(), Time::GetDeltaTime());

			for (Layer* layer : m_LayerStack)
			{
				layer->OnUpdate();
			}

			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
			{
				layer->OnImGuiRender();
			}
			m_ImGuiLayer->End();

			//auto[x, y] = Input::GetMousePosition();
			//BH_CORE_TRACE("{0},{1}", x, y);

			m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClosed(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}
}
