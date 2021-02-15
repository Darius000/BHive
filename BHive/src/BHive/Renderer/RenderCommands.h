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

		inline static void EnableDepthTest()
		{
			s_RendererAPI->EnableDepthTest();
		}

		inline static void DisableDepthTest()
		{
			s_RendererAPI->DisableDepthTest();
		}

		inline static void BindTexture(uint32 slot, uint32 textureID)
		{
			s_RendererAPI->BindTexture(slot, textureID);
		}

		inline static void UnBindTexture(uint32 slot)
		{
			s_RendererAPI->UnBindTexture(slot);
		}

		inline static void EnableCulling()
		{
			s_RendererAPI->EnableBackFaceCulling(true);
		}

		inline static void DisableCulling()
		{
			s_RendererAPI->EnableBackFaceCulling(false);
		}

	private:
		static RendererAPI* s_RendererAPI;

	public:
		
	};
}