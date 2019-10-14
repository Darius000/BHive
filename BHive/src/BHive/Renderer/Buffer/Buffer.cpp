#include "BHivePCH.h"
#include "BHive/Renderer/Buffer/Buffer.h"
#include "BHive/Renderer/Renderer.h"
#include "OpenGLBuffer.h"

namespace BHive
{

	VertexBuffer* VertexBuffer::Create(float* vertices, uint32 size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None: BH_CORE_ASSERT(false, "RendererAPI::None currently not supported"); return nullptr;
		case RendererAPI::OpenGL: return new OpenGLVertexBuffer(vertices, size);
		}

		BH_CORE_ASSERT(false, "Unknown API");
		return nullptr;
	}

	IndexBuffer* IndexBuffer::Create(uint32* indices, uint32 size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None: BH_CORE_ASSERT(false, "RendererAPI::None currently not supported"); return nullptr;
		case RendererAPI::OpenGL: return new OpenGLIndexBuffer(indices, size);
		}

		BH_CORE_ASSERT(false, "Unknown API");
		return nullptr;
	}

}