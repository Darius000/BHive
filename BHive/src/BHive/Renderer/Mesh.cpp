#include "BHivePCH.h"
#include <glad/glad.h>
#include "BHive/Renderer/Renderer.h"
#include "BHive/Renderer/VertexArray.h"
#include "Buffer.h"
#include "Mesh.h"

namespace BHive
{
	FMesh::FMesh()
		:m_VertexArray(nullptr)
	{

	}

	FMesh::FMesh(const FMesh& Other)
	{
		m_VertexArray.reset(Other.m_VertexArray.get());
	}

	void FMesh::Render()
	{
		Renderer::Draw(m_VertexArray);
	}

	void FMesh::SetVerticesAndIndices(const std::vector<float>& Vertices, const std::vector<uint32>& Indices)
	{
		m_Vertices = Vertices;
		m_Indices = Indices;

		CreateBuffers();
	}

	void FMesh::CreateBuffers()
	{
		m_VertexArray.reset(VertexArray::Create());

		BufferLayout layout = {
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float3, "a_Color"},
			{ ShaderDataType::Float2, "a_TexCoord"},
			{ ShaderDataType::Float3, "a_Normal" }
		};

		Ref<VertexBuffer> m_VertexBuffer;
		m_VertexBuffer.reset(VertexBuffer::Create(m_Vertices.data(), (uint32)(m_Vertices.size() * sizeof(float))));
		m_VertexBuffer->SetLayout(layout);

		m_VertexArray->AddVertexBuffer(m_VertexBuffer);

		Ref<IndexBuffer> m_IndexBuffer;
		m_IndexBuffer.reset(IndexBuffer::Create(m_Indices.data(), (uint32)(m_Indices.size() * sizeof(uint32))));

		m_VertexArray->SetIndexBuffer(m_IndexBuffer);
	}

}