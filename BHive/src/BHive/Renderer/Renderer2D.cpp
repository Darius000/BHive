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

	void Renderer2D::Begin(const LinearColor4& clearcolor)
	{
		RenderCommands::SetClearColor(clearcolor);
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