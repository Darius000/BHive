#include "BHivePCH.h"
#include "Triangle.h"
#include <glad/glad.h>
#include "BHive/Entities/Entity.h"

namespace BHive
{
	void Triangle::ComponentInit()
	{
		SetPoints(Vector3(-.5f, -.5f, 0.0f), Vector3(.5f, -.5f, 0.0f), Vector3(0.0f, .5f, 0.0f));
	}

	void Triangle::ComponentStart()
	{
		
	}

	void Triangle::ComponentUpdate(float DeltaTime)
	{
		glBindVertexArray(m_VertexArray);
		glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);
	}

	void Triangle::SetPoints(Vector3& p0, Vector3& p1, Vector3& p2)
	{
		glGenVertexArrays(1, &m_VertexArray);
		glBindVertexArray(m_VertexArray);

		Vector3 p3 = p0 + GetRelativePosition();
		Vector3 p4 = p1 + GetRelativePosition();
		Vector3 p5 = p2 + GetRelativePosition();

		BH_CORE_TRACE("P0:{0}, P1:{1}, P2:{2}", p3.ToString(), p4.ToString(), p5.ToString());

		//p3.Normalize();
		//p4.Normalize();
		//p5.Normalize();

		//BH_CORE_TRACE("P0:{0}, P1:{1}, P2:{2}", p3.ToString(), p4.ToString(), p5.ToString());

		Vector3 vertices[3] = {
			p3,
			p4, 
			p5
		};

		m_VertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices) / sizeof(Vector3)));

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vector3), nullptr);

		unsigned int indices[3] = { 0, 1, 2 };
		m_IndexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32)));
		
	}
}