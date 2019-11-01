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
		m_Vertices = 
		{
			-m_Width / 2.0f, -m_Height / 2.0f, 0.0f, 0.0f, 1.0f, 0.0f,  0.0f, 0.0f,
			m_Width / 2.0f, -m_Height / 2.0f, 0.0f, 0.0f, 1.0f, 0.0f,  1.0f, 0.0f,
			m_Width / 2.0f, m_Height / 2.0f, 0.0f, 0.0f, 1.0f, 0.0f,  1.0f, 1.0f,
			-m_Width / 2.0f, m_Height / 2.0f, 0.0f, 0.0f, 1.0f, 0.0f,  0.0f, 1.0f
		};

		m_Indices = 
		{
			0, 1, 2, 2, 3, 0
		};
	}
}