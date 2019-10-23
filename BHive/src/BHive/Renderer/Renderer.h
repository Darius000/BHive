#pragma once

#include "RenderCommands.h"
#include "Scene/Scene.h"

namespace BHive
{
	class Renderer
	{
	public:
		static void Init();
		static void OnWindowResized(uint32 width, uint32 height);

		static void AddScene(std::shared_ptr<Scene> scene);
		static void RemoveScene(std::shared_ptr<Scene> scene);

		static void BeginScene(uint32 index); 
		static void UpdateScene(const Time& time);
		static void EndScene(); 
		static void Draw(const std::shared_ptr<VertexArray>& vertexArray);

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); };

	private:
		
		static std::vector<std::shared_ptr<Scene>> s_Scenes;
		static std::shared_ptr<Scene> s_Scene;
		static uint32 s_SceneIndex;
	};
	
}
