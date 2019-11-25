#include "BHivePCH.h"
#include "ImGuiLayer.h"



#include "examples/imgui_impl_glfw.h"
#include "examples/imgui_impl_opengl3.h"

#include "BHive/Core/Application.h"

//TEMP
#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace BHive
{
	ImGuiLayer::ImGuiLayer()
		:Layer("ImGuiLayer"), m_Style(Make_Scope<ImGuiStyle>())
	{

	}

	ImGuiLayer::~ImGuiLayer()
	{

	}

	void ImGuiLayer::OnAttach()
	{
		// Setup Dear ImGui context
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
		//io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoTaskBarIcons;
		//io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoMerge;

		// Setup Dear ImGui style
		ImGui::StyleColorsDark(m_Style.get());
		//ImGui::StyleColorsClassic();

		// When view ports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			m_Style->WindowRounding = 0.0f;
			m_Style->Colors[ImGuiCol_WindowBg].w = 1.0f;
		}

		Application& app = Application::Get();
		auto* window = static_cast<GLFWwindow*>(app.GetWindow().GetNativeWindow());

		// Setup Platform/Renderer bindings
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init("#version 410");
	}

	void ImGuiLayer::OnDetach()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void ImGuiLayer::OnImGuiRender()
	{	
		if (ImGui::BeginMainMenuBar())
		{
			if (ImGui::BeginMenu("Menu"))
			{
				ShowMenuItems();
				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Windows"))
			{
				ShowWindowItems();
				ImGui::EndMenu();
			}

			ImGui::EndMainMenuBar();
		}

		if (m_ShowStyleEditor)
		{
			ImGui::Begin("Style Editor", &m_ShowStyleEditor);
			ImGui::ShowStyleEditor(m_Style.get());
			ImGui::End();
		}

		if (m_ShowDemoWindow)
		{
			ImGui::ShowDemoWindow(&m_ShowDemoWindow);
		}

		if (m_ShowProfiler)
		{
			ShowProfiler(&m_ShowProfiler);
		}
	}

	void ImGuiLayer::Begin()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	void ImGuiLayer::End()
	{
		ImGuiIO& io = ImGui::GetIO();
		Application& app = Application::Get();
		io.DisplaySize = ImVec2((float)app.GetWindow().GetWidth(), (float)app.GetWindow().GetHeight());

		// Rendering
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
		}
	}

	void ImGuiLayer::ShowMenuItems()
	{
		ImGui::MenuItem("(dummy menu)", nullptr, false, false);
		if (ImGui::MenuItem("New")) {}
		if (ImGui::MenuItem("Open", "Ctrl+O")) {}
	
		if (ImGui::MenuItem("Save", "Ctrl+S")) {}
		if (ImGui::MenuItem("Save As..")) {}
	}

	void ImGuiLayer::ShowWindowItems()
	{
		if (ImGui::MenuItem("Style Editor"))
		{
			m_ShowStyleEditor = true;
		}

		if (ImGui::MenuItem("Demo Window"))
		{
			m_ShowDemoWindow = true;
		}

		if (ImGui::MenuItem("Profiler"))
		{
			m_ShowProfiler = true;
		}
	}

	void ImGuiLayer::ShowProfiler(bool *open)
	{
		/*if (ImGui::Begin("Profiler", open))
		{
			for (auto& result : InstrumentionTimer::ProfilerResults)
			{
				const char* label = Format("%.3fms %s", result.m_Duration, result.m_Name);
				ImGui::Text(label, result.m_Duration);
			}

			InstrumentionTimer::ProfilerResults.clear();

			ImGui::End();
		}*/
	}

	/*bool ImGuiLayer::m_ShowStyleEditor = false;
	bool ImGuiLayer::m_ShowDemoWindow = false;
	bool ImGuiLayer::m_ShowProfiler = false;*/
}