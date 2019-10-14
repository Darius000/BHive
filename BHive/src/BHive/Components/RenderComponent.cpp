#include "BHivePCH.h"
#include <glad/glad.h>
#include "RenderComponent.h"
//#include "Cameras/Camera.h"
//#include "GameStatics.h"


namespace BHive
{
	RenderComponent::RenderComponent()
		:m_VertexBuffer(nullptr), m_IndexBuffer(nullptr),
		m_VertexArray(-1)
	{

	}

	RenderComponent::RenderComponent(const RenderComponent& other)
	{
		m_VertexArray	= other.m_VertexArray;
		m_VertexBuffer	= VertexBuffer::Create(m_Vertices, GetVertexArraySize());
		m_IndexBuffer	= IndexBuffer::Create(m_Indices, GetIndexArraySize());
	}

	RenderComponent::~RenderComponent()
	{
		delete m_IndexBuffer;
		delete m_VertexBuffer;

		if (m_Vertices != nullptr)
		{
			delete[] m_Vertices;
		}

		if (m_Indices != nullptr)
		{
			delete[] m_Indices;
		}
	}


	void RenderComponent::ComponentInit()
	{

	}

	void RenderComponent::ComponentStart()
	{
		Super::ComponentStart();

		UpdateBuffers();	
	}

	void RenderComponent::ComponentUpdate(float deltaTime)
	{
		Super::ComponentUpdate(deltaTime);

		glBindVertexArray(m_VertexArray);
		glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetSize(), GL_UNSIGNED_INT, nullptr);
	}

	void RenderComponent::OnTransformUpdated(const Transform& transform)
	{
		////Update vertex positions relative to absolute location
		//for (uint32 i = 0; (uint32)i < sizeof(m_Vertices) / sizeof(float); i++)
		//{
		//	Vector3 absLoc = GetAbsoluteLocation();
		//	m_Vertices[i] += absLoc;
		//}

		UpdateBuffers();
	}

	void RenderComponent::UpdateBuffers()
	{
		if (m_VertexArray == -1)
		{
			glGenVertexArrays(1, &m_VertexArray);
		}

		glBindVertexArray(m_VertexArray);

		if (m_VertexBuffer != nullptr)
			delete m_VertexBuffer;
		
		m_VertexBuffer = VertexBuffer::Create(m_Vertices, GetVertexArraySize());

		{
			BufferLayout layout = {
				{ ShaderDataType::Float3, "a_Position" },
				{ ShaderDataType::Float4, "a_Color"}
			};

			m_VertexBuffer->SetLayout(layout);
		}

		uint32 index = 0;
		const auto& layout = m_VertexBuffer->GetLayout();
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


		//offset by 12 bytes 3 * 4 and size is number of floats
		//glEnableVertexAttribArray(1);
		//glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (const void*)12);

		if (m_IndexBuffer != nullptr)
			delete m_IndexBuffer;

		m_IndexBuffer = IndexBuffer::Create(m_Indices, GetIndexArraySize());
	}
}