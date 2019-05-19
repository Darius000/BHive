#pragma once

#include "BHive/Components/TransformComponent.h"

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
		unsigned int m_VertexArray, m_VertexBuffer, m_IndexBuffer;
	};
}