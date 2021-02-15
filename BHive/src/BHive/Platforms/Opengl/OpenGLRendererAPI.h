#pragma once

#include "BHive/Renderer/RendererAPI.h"

namespace BHive
{
	class OpenGLRendererAPI : public RendererAPI
	{

	public:
		void Init() override;
		void SetClearColor(const LinearColor4& color) override;
		void Clear() override;
		void SetViewport(uint32 x, uint32 y, uint32 width, uint32 height) override;
		void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) override;
		void EnableBackFaceCulling(bool enable) override;
		void EnableDepthTest() override;
		void DisableDepthTest() override;
		void BindTexture(uint32 slot, uint32 textureID) override;
		void UnBindTexture(uint32 slot) override;
		
		static float m_LineWidth;
		static float m_PointSize;
	};
}