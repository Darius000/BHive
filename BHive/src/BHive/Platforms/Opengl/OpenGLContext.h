#pragma once

#include "BHive/Renderer/GraphicsContext.h"



struct GLFWwindow;

namespace BHive
{
	class OpenGLContext : public GraphicsContext
	{

	public:
		OpenGLContext(GLFWwindow* windowHandle);

		virtual void Init() override;
		virtual void SwapBuffers() override;

	protected:
		void SetOpenGLStates();

	private:
		GLFWwindow* m_WindowHandle;
	};
}