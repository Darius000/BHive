#pragma once


#include "Buffer.h"

namespace BHive
{
	typedef uint32 RenderID;

	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(Vector3* vertices, uint32 count);
		virtual ~OpenGLVertexBuffer();
		virtual void Bind() const override;
		virtual void UnBind() const override;
		virtual uint32 GetCount() const override { return m_Count; };
	private:
		RenderID m_RenderID;
		uint32 m_Count;
	};

	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(uint32* indices, uint32 count);
		virtual ~OpenGLIndexBuffer();
		virtual void Bind() const override;
		virtual void UnBind() const override;
		virtual uint32 GetCount() const override { return m_Count; };
	private:
		RenderID m_RenderID;
		uint32 m_Count;
	};
}