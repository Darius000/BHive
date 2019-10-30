#pragma once

#include "BHive/Renderer/RendererAPI.h"

namespace BHive
{
	class OpenGLRendererAPI : public RendererAPI
	{

	public:
		virtual void Init() override;
		virtual void SetClearColor(const LinearColor& color) override;
		virtual void Clear() override;
		virtual void SetViewport(uint32 x, uint32 y, uint32 width, uint32 height) override;
		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) override;
	};
}