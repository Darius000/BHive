#pragma once

#include "BHive/Components/Primitive.h"

namespace BHive
{
	class BHive_API Triangle : public PrimitiveComponent
	{
		BCLASS(Triangle, PrimitiveCategory, PrimitiveComponent)

	public:
		Triangle();
		Triangle(float height, float width);

	public:
		void SetHeight(float height);
		void SetWidth(float width);

	private:
		float m_Height;
		float m_Width;

	protected:
		virtual void CreatePrimitive() override;
	};
}