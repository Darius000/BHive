#pragma once

#include "RenderCommands.h"

namespace BHive
{
	class Renderer2D
	{
	public:
		static void Init();
		static void ShutDown();

		static void Begin(const LinearColor4& clearcolor);
		static void End();

		static void Draw(const std::shared_ptr<VertexArray>& vertexArray);

		static void OnWindowResized(uint32 width, uint32 height);
	};
}