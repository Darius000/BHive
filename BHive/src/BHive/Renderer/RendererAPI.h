#pragma once

#include "VertexArray.h"

namespace BHive
{
	class RendererAPI
	{
	public:
		enum class API
		{
			None = 0, OpenGL = 1, DirectX = 2
		};

	public:
		virtual void Init() = 0;
		virtual void SetClearColor(const LinearColor4& color) = 0;
		virtual void Clear() = 0;
		virtual void SetViewport(uint32 x, uint32 y, uint32 width, uint32 height) = 0;

		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) = 0;
		virtual void EnableDepthTest() = 0;
		virtual void DisableDepthTest() = 0;
		virtual void EnableBackFaceCulling(bool enable) = 0;
		virtual void BindTexture(uint32 slot, uint32 textureID) = 0;
		virtual void UnBindTexture(uint32 slot) = 0;


		inline static API GetAPI() { return s_API; }

	private:
		static API s_API;
	};
}