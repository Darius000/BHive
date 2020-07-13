#include "BHivePCH.h"
#include "BHive/Renderer/Buffer.h"
#include "BHive/Renderer/Renderer.h"
#include "BHive/Platforms/OpenGl/OpenGLBuffer.h"

namespace BHive
{

	VertexBuffer* VertexBuffer::Create(std::vector<FVertex> Vertices)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None: BH_CORE_ASSERT(false, "RendererAPI::None currently not supported"); return nullptr;
			case RendererAPI::API::OpenGL: return new OpenGLVertexBuffer(Vertices);
		}

		BH_CORE_ASSERT(false, "Unknown API");
		return nullptr;
	}

	IndexBuffer* IndexBuffer::Create(std::vector<uint32> Indices)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None: BH_CORE_ASSERT(false, "RendererAPI::None currently not supported"); return nullptr;
			case RendererAPI::API::OpenGL: return new OpenGLIndexBuffer(Indices);
		}

		BH_CORE_ASSERT(false, "Unknown API");
		return nullptr;
	}

}