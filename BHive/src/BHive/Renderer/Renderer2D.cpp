#include "BHivePCH.h"
#include "Renderer2D.h"

namespace BHive
{

	void Renderer2D::Init()
	{
		RenderCommands::Init();
	}

	void Renderer2D::ShutDown()
	{

	}

	void Renderer2D::AddScene(Ref<Scene> scene)
	{
		s_Scenes.push_back(scene);
	}

	void Renderer2D::RemoveScene(Ref<Scene> scene)
	{
		std::vector<Ref<Scene>>::iterator s = std::find(s_Scenes.begin(), s_Scenes.end(), scene);

		if (s != s_Scenes.end())
			s_Scenes.erase(s);
	}

	void Renderer2D::BeginScene(uint32 index)
	{
		if (index > 0 && index < s_Scenes.size())
			s_SceneIndex = index;
		s_Scene = s_Scenes[index];
		s_Scene->Begin();
	}

	void Renderer2D::UpdateScene(const Time& time)
	{
		RenderCommands::SetClearColor(BHive::Color(10, 10, 10, 255));
		RenderCommands::Clear();

		if (s_Scenes[s_SceneIndex])
			s_Scenes[s_SceneIndex]->Update(time);
	}

	void Renderer2D::EndScene()
	{
		s_Scene->End();
	}

	void Renderer2D::Draw(const std::shared_ptr<VertexArray>& vertexArray)
	{
		vertexArray->Bind();
		RenderCommands::DrawIndexed(vertexArray);
	}

	void Renderer2D::OnWindowResized(uint32 width, uint32 height)
	{
		RenderCommands::SetViewport(0, 0, width, height);
	}

	std::vector<Ref<Scene>> Renderer2D::s_Scenes;

	Ref<Scene> Renderer2D::s_Scene;

	uint32 Renderer2D::s_SceneIndex;
}