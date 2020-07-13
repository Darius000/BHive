#include "BHivePCH.h"
#include "OpenGLBuffer.h"
#include <glad/glad.h>

namespace BHive
{
	///////////////////////////////////////////////////
	//Vertex Buffer////////////////////////////////////
	///////////////////////////////////////////////////

	OpenGLVertexBuffer::OpenGLVertexBuffer(std::vector<FVertex> Vertices)
	{
		
		glGenBuffers(1, &m_RenderID);
		glBindBuffer(GL_ARRAY_BUFFER, m_RenderID);
		glBufferData(GL_ARRAY_BUFFER,(uint32)( Vertices.size() * sizeof(FVertex)), Vertices.data(), GL_STATIC_DRAW);
	}

	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		glDeleteBuffers(1, &m_RenderID);
	}

	void OpenGLVertexBuffer::Bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_RenderID);
	}

	void OpenGLVertexBuffer::UnBind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void OpenGLVertexBuffer::SetLayout(const BufferLayout& layout)
	{
		m_Layout = layout;
	}

	const BHive::BufferLayout& OpenGLVertexBuffer::GetLayout() const
	{
		return m_Layout;
	}

	///////////////////////////////////////////////
	//Index Buffer/////////////////////////////////
	///////////////////////////////////////////////

	OpenGLIndexBuffer::OpenGLIndexBuffer(std::vector<uint32> Indices)
		:m_Size((uint32)(Indices.size() * sizeof(uint32)))
	{
		glGenBuffers(1, &m_RenderID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RenderID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, (uint32)(Indices.size() * sizeof(uint32)), Indices.data(), GL_STATIC_DRAW);
	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		glDeleteBuffers(1, &m_RenderID);
	}

	void OpenGLIndexBuffer::Bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RenderID);
	}

	void OpenGLIndexBuffer::UnBind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}