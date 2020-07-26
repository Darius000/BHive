#include "BHivePCH.h"
#include "Framebuffer.h"

#include "Bhive/Renderer/Renderer.h"
#include "BHive/Platforms/Opengl/OpenGlFramebuffer.h"

namespace BHive
{

	Ref<FrameBuffer> FrameBuffer::Create(const FrameBufferSpecification& spec)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: BH_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL: return Make_Ref<OpenglFramebuffer>(spec);
		case RendererAPI::API::DirectX: break;
		}

		BH_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}