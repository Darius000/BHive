#pragma once

#include "RenderCommands.h"
#include "Scene/Scene.h"

namespace BHive
{
	class Renderer2D
	{
	public:
		static void Init();
		static void ShutDown();

		static void AddScene(Ref<Scene> scene);
		static void RemoveScene(Ref<Scene> scene);

		static void BeginScene(uint32 index);
		static void UpdateScene(const Time& time);
		static void EndScene();

		static void Draw(const std::shared_ptr<VertexArray>& vertexArray);

		static void OnWindowResized(uint32 width, uint32 height);

		//Primitives
		static std::vector<Ref<Scene>> s_Scenes;
		static Ref<Scene> s_Scene;
		static uint32 s_SceneIndex;
	};
}