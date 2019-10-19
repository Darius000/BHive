#include "BHivePCH.h"
#include "OpenGLVertexArray.h"
#include <glad/glad.h>

namespace BHive
{
	static GLenum ShaderDataTypeToOpenGlBaseType(ShaderDataType type)
	{
		switch (type)
		{
		case BHive::ShaderDataType::Float:	return GL_FLOAT;
		case BHive::ShaderDataType::Float2: return GL_FLOAT;
		case BHive::ShaderDataType::Float3: return GL_FLOAT;
		case BHive::ShaderDataType::Float4: return GL_FLOAT;
		case BHive::ShaderDataType::Mat3:	return GL_FLOAT;
		case BHive::ShaderDataType::Mat4:	return GL_FLOAT;
		case BHive::ShaderDataType::Int:	return GL_INT;
		case BHive::ShaderDataType::Int2:	return GL_INT;
		case BHive::ShaderDataType::Int3:	return GL_INT;
		case BHive::ShaderDataType::Int4:	return GL_INT;
		case BHive::ShaderDataType::Bool:	return GL_BOOL;
		}

		BH_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	OpenGLVertexArray::OpenGLVertexArray()
	{
		glGenVertexArrays(1, &m_RendererID);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &m_RendererID);
	}

	void OpenGLVertexArray::Bind() const
	{
		glBindVertexArray(m_RendererID);
	}

	void OpenGLVertexArray::UnBind() const
	{
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
	{
		BH_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "vertex Buffer has no layout");

		glBindVertexArray(m_RendererID);
		vertexBuffer->Bind();

		uint32 index = 0;
		const auto& layout = vertexBuffer->GetLayout();
		for (const auto& element : layout)
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(
				index,
				element.GetComponentCount(),
				ShaderDataTypeToOpenGlBaseType(element.Type),
				element.Normalized ? GL_TRUE : GL_FALSE,
				layout.GetStride(),
				(const void*)element.Offset);
			index++;
		}

		m_VertexBuffers.push_back(vertexBuffer);
	}

	void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
	{
		glBindVertexArray(m_RendererID);
		indexBuffer->Bind();

		m_IndexBuffer = indexBuffer;
	}

	const std::vector<std::shared_ptr<VertexBuffer>>& OpenGLVertexArray::GetVertexBuffers() const
	{
		return m_VertexBuffers;
	}

	const std::shared_ptr<IndexBuffer>& OpenGLVertexArray::GetIndexBuffer() const
	{
		return m_IndexBuffer;
	}

}