#include "BHivePCH.h"
#include "EditorTime.h"

#include "GLFW/glfw3.h"

namespace BHive
{

	Time::Time()
	{
		
	}

	Time::~Time()
	{

	}

	float Time::GetTime()
	{
		return m_Time;
	}

	float Time::GetDeltaTime()
	{
		return m_DeltaTime;
	}

	void Time::Update()
	{
		m_Time = (float)glfwGetTime();
		m_DeltaTime = m_Time > 0.0f ? m_Time - m_LastTime : (1.0f / 60.0f);
		m_LastTime = m_Time;
	}

	float Time::m_DeltaTime;

	float Time::m_LastTime;

	float Time::m_Time;
}