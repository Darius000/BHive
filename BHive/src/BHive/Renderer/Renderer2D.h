#pragma once

#include "RenderCommands.h"
#include "BHive/Renderer/Mesh.h"

namespace BHive
{
	class Renderer2D
	{
	public:
		static void Init();
		static void ShutDown();

		static void Begin();
		static void End();

		static Ref<Model> Plane(float width, float height);
		static Ref<Model> Triangle(float width, float height);

		static void Draw(const std::shared_ptr<VertexArray>& vertexArray);

		static void OnWindowResized(uint32 width, uint32 height);
	};
}