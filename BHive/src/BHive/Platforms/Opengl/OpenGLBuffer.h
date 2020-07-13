#pragma once

#include "BHive/Renderer/Buffer.h"

namespace BHive
{
	using RenderID = uint32;

	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(std::vector<FVertex> Vertices);
		virtual ~OpenGLVertexBuffer();
		virtual void Bind() const override;
		virtual void UnBind() const override;
		//virtual uint32 GetSize() const override { return m_Size; };

		virtual void SetLayout(const BufferLayout& layout) override;
		virtual const BufferLayout& GetLayout() const override;

	private:
		RenderID m_RenderID;
		//uint32 m_Size;
		BufferLayout m_Layout;
	};

	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(std::vector<uint32> Indices);
		virtual ~OpenGLIndexBuffer();
		virtual void Bind() const override;
		virtual void UnBind() const override;
		virtual uint32 GetSize() const override { return m_Size; };
	private:
		RenderID m_RenderID;
		uint32 m_Size;
	};
}