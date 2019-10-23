#include "BHivePCH.h"
#include "Renderer.h"
#include "Renderer2D.h"

namespace BHive
{
	void Renderer::Init()
	{
		RenderCommands::Init();
	}

	void Renderer::OnWindowResized(uint32 width, uint32 height)
	{
		RenderCommands::SetViewport(0, 0, width, height);
	}

	void Renderer::AddScene(std::shared_ptr<Scene> scene)
	{
		s_Scenes.push_back(scene);
	}

	void Renderer::RemoveScene(std::shared_ptr<Scene> scene)
	{
		std::vector<std::shared_ptr<Scene>>::iterator s = std::find(s_Scenes.begin(), s_Scenes.end(), scene);

		if (s != s_Scenes.end())
			s_Scenes.erase(s);
	}

	void Renderer::BeginScene(uint32 index)
	{
		if (index > 0 && index < s_Scenes.size())
			s_SceneIndex = index;
			s_Scene = s_Scenes[index];
			s_Scene->Begin();
	}

	void Renderer::UpdateScene(const Time& time)
	{
		if(s_Scenes[s_SceneIndex])
			s_Scenes[s_SceneIndex]->Update(time);
	}

	void Renderer::EndScene()
	{
		s_Scene->End();
	}

	void Renderer::Draw(const std::shared_ptr<VertexArray>& vertexArray)
	{
		vertexArray->Bind();
		RenderCommands::DrawIndexed(vertexArray);
	}


	std::vector<std::shared_ptr<BHive::Scene>> Renderer::s_Scenes;

	glm::uint32 Renderer::s_SceneIndex = 0;

	std::shared_ptr<BHive::Scene> Renderer::s_Scene;

}