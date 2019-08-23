#include "BHivePCH.h"
#include "Buffer.h"
#include "Renderer.h"
#include "OpenGLBuffer.h"

namespace BHive
{

	VertexBuffer* VertexBuffer::Create(Vector3* vertices, uint32 count)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None: BH_CORE_ASSERT(false, "RendererAPI::None currently not supported"); return nullptr;
		case RendererAPI::OpenGL: return new OpenGLVertexBuffer(vertices, count);
		}

		BH_CORE_ASSERT(false, "Unknown API");
		return nullptr;
	}

	IndexBuffer* IndexBuffer::Create(uint32* indices, uint32 count)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None: BH_CORE_ASSERT(false, "RendererAPI::None currently not supported"); return nullptr;
		case RendererAPI::OpenGL: return new OpenGLIndexBuffer(indices, count);
		}

		BH_CORE_ASSERT(false, "Unknown API");
		return nullptr;
	}

}