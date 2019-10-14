#pragma once

//#include "BHive/Components/TransformComponent.h"
//#include "Renderer/Buffer.h"
#include "Primitive.h"

namespace BHive
{
	class BHive_API Triangle : public PrimitiveComponent
	{
		BCLASS(Triangle, PrimitiveCategory, PrimitiveComponent)

	public:
		Triangle();
		Triangle(float height, float width);

		//Set height of the triangle
		void SetHeight(float height);
		//set base length of triangle
		void SetWidth(float width);

	private:
		float m_Height;
		float m_Width;

	protected:
		virtual void CreatePrimitive() override;

		virtual uint32 GetVertexArraySize() const override;

		virtual uint32 GetIndexArraySize() const override;

	};
}