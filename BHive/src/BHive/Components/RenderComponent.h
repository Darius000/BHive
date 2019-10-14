#pragma once

#include "TransformComponent.h"
//#include "Assets/Shader.h"
#include "BHive/Renderer/Buffer/Buffer.h"

namespace BHive
{
	class BHive_API RenderComponent : public TransformComponent
	{
		BCLASS(RenderComponent, ComponentCategory, TransformComponent)

	public:
		RenderComponent();
		RenderComponent(const RenderComponent& other);
		virtual ~RenderComponent();

		virtual void ComponentInit() override;
		virtual void ComponentStart() override;
		virtual void ComponentUpdate(float deltaTime) override;
		virtual void OnTransformUpdated(const Transform& transform);
		void UpdateBuffers();

	protected:
		float* m_Vertices;
		uint32* m_Indices;
		virtual uint32 GetVertexArraySize() const { return 0; }
		virtual uint32 GetIndexArraySize() const { return 0; }

	private:
		unsigned int m_VertexArray;
		VertexBuffer* m_VertexBuffer;
		IndexBuffer* m_IndexBuffer;
		
	};
}
