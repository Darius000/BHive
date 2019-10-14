#include "BHivePCH.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace BHive
{

	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		:m_WindowHandle(windowHandle)
	{
		BH_CORE_ASSERT(windowHandle, "Window handle is null!");
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		BH_CORE_ASSERT(status, "Failed to initialize Glad!");

		BH_CORE_INFO("OpenGl Info:");
		BH_CORE_INFO(" Vendor: {0}", glGetString(GL_VENDOR));
		BH_CORE_INFO(" Renderer: {0}", glGetString(GL_RENDERER));
		BH_CORE_INFO(" Version: {0}", glGetString(GL_VERSION));

		int attributes;
		glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &attributes);
		BH_CORE_INFO(" Vertex attributes supported: {0}", attributes);

		SetOpenGLStates();
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}

	void OpenGLContext::SetOpenGLStates()
	{
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_MULTISAMPLE);
		glLineWidth(1.0f);
		glEnable(GL_LINE_SMOOTH);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

}