#include "BHivePCH.h"
#include <glad/glad.h>
#include "BHive/Renderer/Renderer.h"
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

	FMesh::FMesh(const std::vector<FVertex>& Vertices, const std::vector<uint32>& Indices, const std::vector<FFace>& Faces)
		:m_Vertices(Vertices), m_Indices(Indices), m_Faces(Faces), m_VertexArray(nullptr)
	{
		CreateBuffers();
	}

	void FMesh::Render()
	{
		if (m_Material)
		{
			m_Material->Render();
		}

		if(m_VertexArray) 
		{
			Renderer::Draw(m_VertexArray);
		}
	}

	void FMesh::SetVerticesAndIndices(const std::vector<FVertex>& Vertices, const std::vector<uint32>& Indices, const std::vector<FFace>& Faces)
	{
		m_Vertices = Vertices;
		m_Indices = Indices;
		m_Faces = Faces;

		if(!m_ImportedTangentAndBitTangents) CalculateTangetsandBitTangets();
		CreateBuffers();
	}

	void FMesh::SetName(const BName& NewName)
	{
		m_Name = NewName;

		//BH_CORE_INFO("{0}", m_Name);
	}

	void FMesh::SetMaterial(Ref<Material> material)
	{
		m_Material = material;
	}

	void FMesh::CalculateTangetsandBitTangets()
	{
		for (auto& face : m_Faces)
		{
			size_t numIndices = face.indices.size();
			for (size_t i = 0; i < numIndices; i+=3)
			{
				uint32 i0 = face.indices[i];
				uint32 i1 = face.indices[(i + 1) % numIndices];
				uint32 i2 = face.indices[(i + 2) % numIndices];

				FVertex& v0 = m_Vertices[i0];
				FVertex& v1 = m_Vertices[i1];
				FVertex& v2 = m_Vertices[i2];

				FVector3& p0 = v0.m_Position;
				FVector3& p1 = v1.m_Position;
				FVector3& p2 = v2.m_Position;

				FVector2& t0 = v0.m_TexCoord;
				FVector2& t1 = v1.m_TexCoord;
				FVector2& t2 = v2.m_TexCoord;

				FVector3 deltaPos1 = p1 - p0;
				FVector3 deltaPos2 = p2 - p0;

				FVector2 deltaUV1 = t1 - t0;
				FVector2 deltaUV2 = t2 - t0;

				float f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV1.y * deltaUV2.x);
				FVector3 tangent = (deltaPos1 * deltaUV2.y - deltaPos2 * deltaUV1.y) * f;
				FVector3 bittangent = (deltaPos2 * deltaUV1.x - deltaPos1 * deltaUV2.x) * f;

				v0.m_Tangent = tangent;
				v1.m_Tangent = tangent;
				v2.m_Tangent = tangent;

				v0.m_BitTangent = bittangent;
				v1.m_BitTangent = bittangent;
				v2.m_BitTangent = bittangent;
			}
			
		}
	}

	void FMesh::CreateBuffers()
	{
		m_VertexArray.reset(VertexArray::Create());

		BufferLayout layout = {
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float4, "a_Color"},
			{ ShaderDataType::Float2, "a_TexCoord"},
			{ ShaderDataType::Float3, "a_Normal" },
			{ ShaderDataType::Float3, "a_Tangent"},
			{ ShaderDataType::Float3, "a_BitTanget"}
		};

		Ref<VertexBuffer> m_VertexBuffer;
		m_VertexBuffer.reset(VertexBuffer::Create(m_Vertices));
		m_VertexBuffer->SetLayout(layout);

		m_VertexArray->AddVertexBuffer(m_VertexBuffer);

		Ref<IndexBuffer> m_IndexBuffer;
		m_IndexBuffer.reset(IndexBuffer::Create(m_Indices));

		m_VertexArray->SetIndexBuffer(m_IndexBuffer);
	}	

	
}