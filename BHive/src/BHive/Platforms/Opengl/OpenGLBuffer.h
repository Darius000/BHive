#pragma once

#include "BHive/Renderer/Buffer.h"

namespace BHive
{
	typedef uint32 RenderID;

	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(float* vertices, uint32 size);
		virtual ~OpenGLVertexBuffer();
		virtual void Bind() const override;
		virtual void UnBind() const override;
		virtual uint32 GetSize() const override { return m_Size; };

		virtual void SetLayout(const BufferLayout& layout) override;
		virtual const BufferLayout& GetLayout() const override;

	private:
		RenderID m_RenderID;
		uint32 m_Size;
		BufferLayout m_Layout;
	};

	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(uint32* indices, uint32 size);
		virtual ~OpenGLIndexBuffer();
		virtual void Bind() const override;
		virtual void UnBind() const override;
		virtual uint32 GetSize() const override { return m_Size; };
	private:
		RenderID m_RenderID;
		uint32 m_Size;
	};
}