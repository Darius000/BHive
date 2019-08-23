#pragma once

namespace BHive
{
	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() {}

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;
		virtual uint32 GetCount() const = 0;

		static VertexBuffer* Create(Vector3* vertices, uint32 count);
	};

	class IndexBuffer
	{
	public:
		virtual ~IndexBuffer(){}

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;
		virtual uint32 GetCount() const = 0;

		static IndexBuffer* Create(uint32* indices, uint32 count);
	};
}