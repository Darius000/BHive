#include "BHivePCH.h"
#include "VertexArray.h"
#include "BHive/Renderer/Renderer.h"
#include "BHive/Platforms/Opengl/OpenGLVertexArray.h"

namespace BHive
{
	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None: BH_CORE_ASSERT(false, "RendererAPI::None currently not supported"); return nullptr;
			case RendererAPI::API::OpenGL: return new OpenGLVertexArray();
		}

		BH_CORE_ASSERT(false, "Unknown API");
		return nullptr;
	}
}