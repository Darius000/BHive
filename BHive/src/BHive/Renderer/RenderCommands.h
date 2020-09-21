#pragma once

#include "RendererAPI.h"

namespace BHive
{
	class RenderCommands
	{
	public:
		inline static void Init()
		{
			s_RendererAPI->Init();
		}

		inline static void SetClearColor(const LinearColor4& color) 
		{
			s_RendererAPI->SetClearColor(color);
		}

		inline static void Clear()
		{
			s_RendererAPI->Clear();
		}

		inline static void SetViewport(uint32 x, uint32 y, uint32 width, uint32 height)
		{
			s_RendererAPI->SetViewport(x, y, width, height);
		}

		inline static void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray)
		{
			s_RendererAPI->DrawIndexed(vertexArray);
		}

		inline static void SetEnableBackfaceCulling(bool enable)
		{
			s_RendererAPI->EnableBackFaceCulling(enable);
		}

	private:
		static RendererAPI* s_RendererAPI;
	};
}