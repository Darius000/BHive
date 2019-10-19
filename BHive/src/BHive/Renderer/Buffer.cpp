#include "BHivePCH.h"
#include "BHive/Renderer/Buffer.h"
#include "BHive/Renderer/Renderer.h"
#include "BHive/Platforms/OpenGl/OpenGLBuffer.h"

namespace BHive
{

	VertexBuffer* VertexBuffer::Create(float* vertices, uint32 size)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None: BH_CORE_ASSERT(false, "RendererAPI::None currently not supported"); return nullptr;
			case RendererAPI::API::OpenGL: return new OpenGLVertexBuffer(vertices, size);
		}

		BH_CORE_ASSERT(false, "Unknown API");
		return nullptr;
	}

	IndexBuffer* IndexBuffer::Create(uint32* indices, uint32 size)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None: BH_CORE_ASSERT(false, "RendererAPI::None currently not supported"); return nullptr;
			case RendererAPI::API::OpenGL: return new OpenGLIndexBuffer(indices, size);
		}

		BH_CORE_ASSERT(false, "Unknown API");
		return nullptr;
	}

}