#pragma once

#include "BHive/Components/TransformComponent.h"
#include "Renderer/Buffer.h"

namespace BHive
{
	class BHive_API Triangle : public TransformComponent
	{
		BCLASS(Triangle, ComponentCategory | PrimitiveCategory, TransformComponent)

	public:
		Triangle() {};
	
		virtual void ComponentInit() override;
		virtual void ComponentStart() override;
		virtual void ComponentUpdate(float DeltaTime) override;
		void SetPoints(Vector3& p0 ,Vector3& p1 ,Vector3& p2);

	private:
		unsigned int m_VertexArray;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;
	};
}