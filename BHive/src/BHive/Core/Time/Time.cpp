#include "BHivePCH.h"
#include "Time.h"

#include "GLFW/glfw3.h"

namespace BHive
{
	void Time::Update()
	{
		m_Time = GetPlatformTime();
		m_DeltaTime = m_Time > 0.0f ? m_Time - m_LastTime : (1.0f / 60.0f);
		m_LastTime = m_Time;
	}

	float WindowsTime::GetPlatformTime()
	{
		return (float)glfwGetTime();
	}

}