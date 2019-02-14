#include "BHivePCH.h"
#include "RenderLayer.h"
#include <glad/glad.h>

namespace BHive
{

	RenderLayer::RenderLayer()
		:Layer("RenderLayer")
	{

	}

	RenderLayer::~RenderLayer()
	{

	}

	void RenderLayer::OnAttach()
	{
		SetOpenGLStates();
		PrintMaxVertexAttributes();
		PrintOpenglInfo();
	}

	void RenderLayer::OnDetach()
	{
		
	}

	void RenderLayer::OnUpdate()
	{
		//BH_INFO("Render::Update");
	}

	void RenderLayer::OnEvent(Event& event)
	{
		
	}

	void RenderLayer::SetOpenGLStates()
	{
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_MULTISAMPLE);
		glLineWidth(1.0f);
		glEnable(GL_LINE_SMOOTH);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	void RenderLayer::PrintMaxVertexAttributes()
	{
		int attributes;
		glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &attributes);
		BH_CORE_INFO("Maximum number of vertex attributes supported: {0}", attributes);
	}

	void RenderLayer::PrintOpenglInfo()
	{
		BH_CORE_INFO(glGetString(GL_VERSION));
	}

}