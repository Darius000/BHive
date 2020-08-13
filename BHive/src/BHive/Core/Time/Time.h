#pragma once

#include "BHive/Core/Core.h"

namespace BHive
{
	class BHive_API Time
	{
	protected:
		Time()
			:m_Time(0.0f), m_LastTime(0.0f), m_DeltaTime(0.0f) {}

	public:
		virtual ~Time() {}

	protected:
		virtual float GetPlatformTime(){ return 0.0f; };

	public:
		float GetTime() const { return m_Time;}
		float GetDeltaTime() const { return m_DeltaTime; }
		void Update();
		float GetSeconds() const { return m_Time; }
		float GetMillisconds() const { return m_Time * 1000.0f; }

	public:
		operator float() const { return m_Time; }

	private:
		float m_Time;
		float m_LastTime;
		float m_DeltaTime;
	};

	class BHive_API WindowsTime : public Time
	{

	public:
		WindowsTime() {}
		virtual ~WindowsTime() {}

	protected:
		float GetPlatformTime() override;
	};
}