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

		int texture_units;
		glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &texture_units);
		BH_CORE_INFO("Max texture units supported: {0}", texture_units);
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}
}