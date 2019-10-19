#ifndef BUFFER_H
#define BUFFER_H

#include <glad/glad.h>

namespace BHive
{
	enum class ShaderDataType : uint8
	{
		None = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool, Struct
	};

	static uint32 ShaderDataTypeSize(ShaderDataType type)
	{
		switch (type)
		{
			case ShaderDataType::Float:		return 4;
			case ShaderDataType::Float2:	return 4 * 2;
			case ShaderDataType::Float3:	return 4 * 3;
			case ShaderDataType::Float4:	return 4 * 4;
			case ShaderDataType::Mat3:		return 4 * 3 *3;
			case ShaderDataType::Mat4:		return 4 * 4 * 4;
			case ShaderDataType::Int:		return 4;
			case ShaderDataType::Int2:		return 4 * 2;
			case ShaderDataType::Int3:		return 4 * 3;
			case ShaderDataType::Int4:		return 4 * 4;
			case ShaderDataType::Bool:		return 1;
			//case ShaderDataType::Struct: return 4;
		}

		BH_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	struct BufferElement
	{
		FString Name;
		ShaderDataType Type;
		uint32 Size;
		uint64 Offset;
		bool Normalized;

		BufferElement() {}
		BufferElement(ShaderDataType type, const FString& name, bool normalized = false)
			:Name(name), Type(type), Size(ShaderDataTypeSize(type)), Offset(0), Normalized(normalized)
		{

		}

		uint32 GetComponentCount() const
		{
			switch (Type)
			{
				case BHive::ShaderDataType::Float:	return 1;
				case BHive::ShaderDataType::Float2: return 2;
				case BHive::ShaderDataType::Float3: return 3;
				case BHive::ShaderDataType::Float4: return 4;
				case BHive::ShaderDataType::Mat3:	return 3 * 3;
				case BHive::ShaderDataType::Mat4:	return 4 * 4;
				case BHive::ShaderDataType::Int:	return 1;
				case BHive::ShaderDataType::Int2:	return 2;
				case BHive::ShaderDataType::Int3:	return 3;
				case BHive::ShaderDataType::Int4:	return 4;
				case BHive::ShaderDataType::Bool:	return 1;
				//case BHive::ShaderDataType::Struct:	return 1;
			}

			BH_CORE_ASSERT(false, "Unknown ShaderDataType!");
			return 0;
		}

	};

	class BufferLayout
	{
	public:
		BufferLayout() {};
		BufferLayout(const std::initializer_list<BufferElement>& elements)
			:m_Elements(elements)
		{
			CalculateOffsetsAndStride();
		}

		inline uint32 GetStride() const { return m_Stride; }
		inline const std::vector<BufferElement>& GetElements() const { return m_Elements; }

		std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
		std::vector<BufferElement>::iterator end() { return m_Elements.end(); }
		std::vector<BufferElement>::const_iterator begin()  const { return m_Elements.begin(); }
		std::vector<BufferElement>::const_iterator end() const { return m_Elements.end(); }

	private:
		void CalculateOffsetsAndStride()
		{
			uint32 offset = 0;
			m_Stride = 0;
			for (auto& element : m_Elements)
			{
				element.Offset = offset;
				offset += element.Size;
				m_Stride += element.Size;
			}
		}
	private:
		std::vector<BufferElement> m_Elements;
		uint32 m_Stride = 0;
	};

	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() {}

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;
		virtual uint32 GetSize() const = 0;

		virtual void SetLayout(const BufferLayout& layout) = 0;
		virtual const BufferLayout& GetLayout() const = 0;

		static VertexBuffer* Create(float* vertices, uint32 size);
	};

	class IndexBuffer
	{
	public:
		virtual ~IndexBuffer(){}

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;
		virtual uint32 GetSize() const = 0;

		static IndexBuffer* Create(uint32* indices, uint32 size);
	};
}

#endif // 