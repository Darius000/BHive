#include "BHivePCH.h"
#include "OpenGLRendererAPI.h"

namespace BHive
{
	void OpenGLRendererAPI::Init()
	{
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_MULTISAMPLE);
		glLineWidth(1.0f);
		glEnable(GL_LINE_SMOOTH);
		glEnable(GL_BLEND);
		EnableBackFaceCulling(true);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glBlendEquation(GL_FUNC_ADD);
	}

	void OpenGLRendererAPI::SetClearColor(const LinearColor4& color)
	{
		glClearColor(color.r, color.g,color.b,color.a);
	}

	void OpenGLRendererAPI::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLRendererAPI::SetViewport(uint32 x, uint32 y, uint32 width, uint32 height)
	{
		glViewport(x, y, width, height);
	}

	void OpenGLRendererAPI::DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray)
	{
		glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetSize(), GL_UNSIGNED_INT, nullptr);
	}


	void OpenGLRendererAPI::EnableBackFaceCulling(bool enable)
	{
		enable ? glEnable(GL_CULL_FACE) : glDisable(GL_CULL_FACE);
	}


	void OpenGLRendererAPI::EnableDepthTest()
	{
		glEnable(GL_DEPTH_TEST);
	}


	void OpenGLRendererAPI::DisableDepthTest()
	{
		glDisable(GL_DEPTH_TEST);
	}


	void OpenGLRendererAPI::BindTexture(uint32 slot, uint32 textureID)
	{
		glBindTextureUnit(slot, textureID);
	}

	void OpenGLRendererAPI::UnBindTexture(uint32 slot)
	{
		glBindTextureUnit(slot, 0);
	}
}