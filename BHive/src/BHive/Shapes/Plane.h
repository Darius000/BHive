#pragma once

#include "BHive/Components/Primitive.h"

namespace BHive
{
	class Plane : public PrimitiveComponent
	{
		BCLASS(Plane, PrimitiveCategory, PrimitiveComponent)

	public:
		Plane() :m_Height(1.0f), m_Width(1.0f) {};
		Plane(float height, float width) :m_Height(height), m_Width(width) {};

	public:
		void SetWidth(float width);
		void SetHeight(float height);

	protected:
		virtual void CreatePrimitive() override;
	private:
		float m_Height;
		float m_Width;
	};
}