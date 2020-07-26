#include "BHivePCH.h"
#include <glad/glad.h>
#include "RenderComponent.h"
#include "BHive/Renderer/Renderer.h"
#include "Managers/AssetManagers.h"


namespace BHive
{
	RenderComponent::RenderComponent()
		//:m_VertexArray(nullptr)
	{
		m_Shader = ShaderLibrary::Get("Default");
		m_Texture = TextureManager::Get("White");
		
		//BH_CORE_TRACE("White tex use count {0}", m_Texture.use_count());
	}

	RenderComponent::RenderComponent(const RenderComponent& other)
		:m_Shader(other.m_Shader)
	{
		//m_VertexArray.reset(other.m_VertexArray.get());
	}

	void RenderComponent::ComponentInit()
	{
		Super::ComponentInit();
		
	}

	void RenderComponent::ComponentStart()
	{
		Super::ComponentStart();

		//CreateBuffers();
	}

	void RenderComponent::ComponentUpdate(const Time& time)
	{
		Super::ComponentUpdate(time);

		Draw();
	}

	void RenderComponent::OnTransformUpdated(const Transform& transform)
	{
		Super::OnTransformUpdated(transform);

		//BH_CORE_TRACE("RenderComponent OnTransformUpdate!");

		if(m_Shader) m_Shader->Bind();
	}

	void RenderComponent::SetShader(Ref<Shader> shader)
	{
		m_Shader = shader;
	}

	void RenderComponent::SetTexture(Ref<Texture2D> texture)
	{
		m_Texture = texture;
	}


	void RenderComponent::SetMesh(Ref<FMesh> Mesh)
	{
		m_Mesh = Mesh;
	}

	void RenderComponent::CreateBuffers()
	{
		/*m_VertexArray.reset(VertexArray::Create());

		BufferLayout layout = {
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float3, "a_Color"},
			{ ShaderDataType::Float2, "a_TexCoord"},
			{ ShaderDataType::Float3, "a_Normal" }
		};

		std::shared_ptr<VertexBuffer> m_VertexBuffer;
		m_VertexBuffer.reset(VertexBuffer::Create(m_Vertices.data(), (uint32)(m_Vertices.size() * sizeof(float))));
		m_VertexBuffer->SetLayout(layout);

		m_VertexArray->AddVertexBuffer(m_VertexBuffer);

		std::shared_ptr<IndexBuffer> m_IndexBuffer;
		m_IndexBuffer.reset(IndexBuffer::Create(m_Indices.data(), (uint32)(m_Indices.size() * sizeof(uint32))));

		m_VertexArray->SetIndexBuffer(m_IndexBuffer);*/
	}

	void RenderComponent::Draw()
	{	
		if (m_Shader)
		{
			m_Shader->Bind();
			m_Shader->SetMat4("u_Model", GetTransform().GetMatrix());
			m_Shader->SetVec4("u_Color", LinearColor(1.0f, 1.0f, 1.0f, 1.0f));
			m_Shader->SetInt("u_Texture", 0);
		}

		if (m_Texture)
		{
			m_Texture->Bind();
		}

		if (m_Mesh)
		{
			m_Mesh->Render();
		}

		/*if (m_VertexArray)
		{
			Renderer::Draw(m_VertexArray);
		}*/
	}
}