#include "BHivePCH.h"
#include "Renderer2D.h"
#include "BHive/Renderer/Shader.h"

namespace BHive
{

	void Renderer2D::Init()
	{
		RenderCommands::Init();
	}

	void Renderer2D::ShutDown()
	{

	}

	void Renderer2D::Begin(const CameraComponent& camera)
	{
		RenderCommands::SetClearColor(BHive::LinearColor(0.2f, 0.2f, 0.2f, 1.0f));
		RenderCommands::Clear();
	}

	void Renderer2D::End()
	{
		
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
}