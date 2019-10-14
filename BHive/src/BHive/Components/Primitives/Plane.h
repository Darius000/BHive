#pragma once

#include "Primitive.h"

namespace BHive
{
	class Plane : public PrimitiveComponent
	{
		BCLASS(Plane, PrimitiveCategory, PrimitiveComponent)

	public:
		Plane() :m_Height(1.0f), m_Width(1.0f) {};

		void SetWidth(float width);
		void SetHeight(float height);

	protected:
		virtual void CreatePrimitive() override;


		virtual uint32 GetVertexArraySize() const override;


		virtual uint32 GetIndexArraySize() const override;

	private:
		float m_Height;
		float m_Width;
	};
}