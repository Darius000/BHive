#include "BHivePCH.h"
#include "Renderer.h"

namespace BHive
{

	void Renderer::SetAPI(RendererAPI API)
	{
		s_RendererAPI = API;
	}

	RendererAPI Renderer::s_RendererAPI = RendererAPI::OpenGL;
}