#include "BHivePCH.h"
#include "Triangle.h"
//#include <glad/glad.h>
//#include "BHive/Entities/Entity.h"

namespace BHive
{

	Triangle::Triangle()
		:m_Height(1.0f), m_Width(1.0f)
	{

	}

	Triangle::Triangle(float height, float base)
		:m_Height(height), m_Width(base)
	{

	}

	void Triangle::SetHeight(float height)
	{
		m_Height = height;

		UpdatePrimitive();
	}

	void Triangle::SetWidth(float width)
	{
		m_Width = width;

		UpdatePrimitive();
	}

	void Triangle::CreatePrimitive()
	{
		m_Vertices = new float[3 * 7]
		{
			-m_Width / 2.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			m_Width / 2.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
			0.0f, m_Height, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f
		};

		m_Indices = new uint32[3]
		{
			0 , 1, 2
		};
	}

	uint32 Triangle::GetVertexArraySize() const
	{
		return sizeof(float) * 3 * 7;
	}

	uint32 Triangle::GetIndexArraySize() const
	{
		return 3 * sizeof(uint32);
	}

}