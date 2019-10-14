#include "BHivePCH.h"
#include "Plane.h"

namespace BHive
{

	void Plane::SetWidth(float width)
	{
		m_Width = width;

		UpdatePrimitive();
	}

	void Plane::SetHeight(float height)
	{
		m_Height = height;

		UpdatePrimitive();
	}

	void Plane::CreatePrimitive()
	{
		m_Vertices = new float[4 * 7] 
		{
			-m_Width / 2.0f, -m_Height / 2.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			m_Width / 2.0f, -m_Height / 2.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
			m_Width / 2.0f, m_Height / 2.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
			-m_Width / 2.0f, m_Height / 2.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		};

		m_Indices = new uint32[6]
		{
			0, 1, 2, 2, 3, 0
		};
	}

	uint32 Plane::GetVertexArraySize() const
	{
		return 4 * 7 * sizeof(float);
	}

	uint32 Plane::GetIndexArraySize() const
	{
		return 6 * sizeof(uint32);
	}

}