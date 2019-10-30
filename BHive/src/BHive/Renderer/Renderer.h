#pragma once

#include "RenderCommands.h"

namespace BHive
{
	class Renderer
	{
	public:
		static void Init();
		static void Shutdown();

		static void Begin(); 
		static void End(); 
		static void Draw(const std::shared_ptr<VertexArray>& vertexArray);

		static void OnWindowResized(uint32 width, uint32 height);

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); };
	};
	
}
