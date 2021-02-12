#include "BHivePCH.h"
#include "Application.h"

#include "BHive/Core/Log.h"
#include "BHive/Font/FontLoader.h"
#include "BHive/Renderer/RendererAPI.h"
#include "BHive/Renderer/Renderer.h"
#include "BHive/Renderer/RenderCommands.h"
#include "BHive/Core/Input.h"
#include "BHive/Renderer/Shader.h"
#include "BHive/Managers/AssetManagers.h"
#include "Platforms/Opengl/OpenGLTexture.h"
#include "BHive/Font/FontFamily.h"
#include "BHive/Importer/AssetImporter.h"

namespace BHive
{
	Application* Application::s_Instance = nullptr;

	Application::Application(const std::string& name)
	{

		BH_CORE_ASSERT(!s_Instance, "Application Already Exists!");
		s_Instance = this;

		m_Window = Scope<Window>(Window::Create(WindowProps(name)));

		//pass window events to application
		m_Window->SetEventCallback(BIND_EVENT(Application::OnEvent));


		//Create default textures
		uint8 WhiteTextureData[] = {0xff, 0xff, 0xff, 0xff, '\0'};
		AssetManager::Add("White", Texture2D::Create(1, 1, GL_RGBA8, GL_RGBA, (void*)&WhiteTextureData));

		//Create default black texture
		uint8 BlackTextureData[] = {0x00, 0x00, 0x00, 0xff, '\0'};
		AssetManager::Add("Black", Texture2D::Create( 1, 1, GL_RGBA8, GL_RGBA, (void*)&BlackTextureData));

		uint8 BlueTextureData[] = {0x80, 0x80, 0xff, 0xff, '\0'};
		AssetManager::Add("Blue", Texture2D::Create( 1, 1, GL_RGB8, GL_RGB, (void*)&BlueTextureData));
	
		LoadAssets();

		Ref<Texture2D> m_WindowsIcon = AssetManager::Get<Texture2D>("folder");
		m_Window->SetIcon(m_WindowsIcon);
		m_Window->SetVSync(false);

		Renderer::Init();

		m_Time = Make_Scope<WindowsTime>();
		m_ImGuiLayer = new ImGuiLayer();

		PushOverlay(m_ImGuiLayer);

		//Load Fonts
		Ref<FontFamily> opensans = Make_Ref<FontFamily>();
		opensans->AddFontToFamily("Regular", R"(..\BHive\Assets\Fonts\OpenSans\OpenSans-Regular.ttf)");
		opensans->AddFontToFamily("Bold", R"(..\BHive\Assets\Fonts\OpenSans\OpenSans-Bold.ttf)");
		opensans->AddFontToFamily("Italic", R"(..\BHive\Assets\Fonts\OpenSans\OpenSans-Italic.ttf)");
		AssetManager::Add("OpenSans", opensans);
	}


	Application::~Application()
	{
		
	}
	
	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(this, &Application::OnWindowClosed);
		dispatcher.Dispatch<WindowResizeEvent>(this, &Application::OnWindowResize);

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

		while (m_Running)
		{
			m_Time->Update();

			if (!m_Minimized)
			{
				for (Layer* layer : m_LayerStack)
				{
					layer->OnUpdate(*m_Time);
				}

				m_ImGuiLayer->Begin();
				for (Layer* layer : m_LayerStack)
				{
					layer->OnImGuiRender();
				}
				m_ImGuiLayer->End();
			}

			m_Window->OnUpdate();
		}
	}


	void Application::Close()
	{
		m_Running = false;
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

	void Application::LoadAssets()
	{	
		BH_PROFILE_SCOPE("Load Engine Assets");
		WinPath EngineAssetFolder("..\\BHive\\Assets");
		WinPath SandBoxAssetFolder("..\\Sandbox\\Assets");
		AssetImporter::ImportDirectoryContents(EngineAssetFolder);
		AssetImporter::ImportDirectoryContents(SandBoxAssetFolder);
	}

}
