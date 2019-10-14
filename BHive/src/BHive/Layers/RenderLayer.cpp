#include "BHivePCH.h"
#include "RenderLayer.h"
#include "BHive/Time/EditorTime.h"
#include "BHive/Statics/GameStatics.h"
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

		/*//Vertex Array
		//Vertex Buffer
		//Index Buffer
		glGenVertexArrays(1, &m_VertexArray);
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

		/*Rotator a = Rotator();
		Rotator b = Rotator(20.0f, 360.0f, 500.0f);
		static float t = 0.0f;
		static Rotator v = Rotator();

		t += Time::GetDeltaTime() * .1f;
		v = MathLibrary::LerpRotator(a, b, t);
		v.roll = MathLibrary::Clamp(v.roll, a.roll, b.roll);
		v.yaw = MathLibrary::Clamp(v.yaw, a.yaw, b.yaw);
		v.pitch = MathLibrary::Clamp(v.pitch, a.pitch, b.pitch);
		v.Normalize();

		BH_CORE_TRACE("value: {0}", v.ToString());*/
	}

	void RenderLayer::OnEvent(Event& event)
	{
		
	}
}