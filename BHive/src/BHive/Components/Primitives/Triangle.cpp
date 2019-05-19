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
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);
	}

	void Triangle::SetPoints(Vector3& p0, Vector3& p1, Vector3& p2)
	{
		glGenVertexArrays(1, &m_VertexArray);
		glBindVertexArray(m_VertexArray);

		glGenBuffers(1, &m_VertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);

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

		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vector3), nullptr);

		glGenBuffers(1, &m_IndexBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);

		unsigned int indices[3] = { 0, 1, 2 };
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		glBindVertexArray(0);
	}
}