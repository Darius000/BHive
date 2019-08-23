#include "BHivePCH.h"
#include "OpenGLBuffer.h"
#include <glad/glad.h>

namespace BHive
{
	///////////////////////////////////////////////////
	//Vertex Buffer////////////////////////////////////
	///////////////////////////////////////////////////

	OpenGLVertexBuffer::OpenGLVertexBuffer(Vector3* vertices, uint32 count)
		:m_Count(count)
	{
		
		glGenBuffers(1, &m_RenderID);
		glBindBuffer(GL_ARRAY_BUFFER, m_RenderID);
		glBufferData(GL_ARRAY_BUFFER, count * sizeof(Vector3), vertices, GL_STATIC_DRAW);
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

	///////////////////////////////////////////////
	//Index Buffer/////////////////////////////////
	///////////////////////////////////////////////

	OpenGLIndexBuffer::OpenGLIndexBuffer(uint32* indices, uint32 count)
		:m_Count(count)
	{
		glGenBuffers(1, &m_RenderID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RenderID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32), indices, GL_STATIC_DRAW);
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