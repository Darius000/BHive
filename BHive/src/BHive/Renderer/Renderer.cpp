#include "BHivePCH.h"
#include "Renderer.h"
#include "Renderer2D.h"

namespace BHive
{
	void Renderer::Init()
	{
		RenderCommands::Init();
	}

	void Renderer::Shutdown()
	{

	}

	void Renderer::OnWindowResized(uint32 width, uint32 height)
	{
		RenderCommands::SetViewport(0, 0, width, height);
	}

	void Renderer::Begin()
	{
		
	}

	void Renderer::End()
	{
		
	}

	void Renderer::Draw(const std::shared_ptr<VertexArray>& vertexArray)
	{
		vertexArray->Bind();
		RenderCommands::DrawIndexed(vertexArray);
	}
}