#include "BHivePCH.h"
#include "RenderLayer.h"
#include "EditorTime.h"
#include "GameStatics.h"
#include <glad/glad.h>

namespace BHive
{
	RenderLayer::RenderLayer()
		:Layer("RenderLayer")
	{
		m_DefaultWorld = new World();
	}

	RenderLayer::~RenderLayer()
	{
		delete m_DefaultWorld;
	}

	void RenderLayer::OnAttach()
	{
		GameStatics::GetWorld()->Start();

		//Vertex Array
		//Vertex Buffer
		//Index Buffer
		/*glGenVertexArrays(1, &m_VertexArray);
		glBindVertexArray(m_VertexArray);

		glGenBuffers(1, &m_VertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);

		float vertices[3 * 3] = {
			-0.5f, -0.5f, -0.0f,
			0.5f, -0.5f, 0.0f,
			0.0f, 0.5f, 0.0f
		};

		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

		glGenBuffers(1, &m_IndexBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);

		unsigned int indices[3] = { 0, 1, 2 };
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		glBindVertexArray(0);*/

	}

	void RenderLayer::OnDetach()
	{
		
	}

	void RenderLayer::OnUpdate()
	{
		GameStatics::GetWorld()->Update(Time::GetDeltaTime());

		/*glBindVertexArray(m_VertexArray); //Need if unbounded to 0
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);*/
	}

	void RenderLayer::OnEvent(Event& event)
	{
		
	}
}