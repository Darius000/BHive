#pragma once

#include "Event.h"

namespace BHive
{

	class BHive_API KeyEvent : public Event
	{
	public:
		inline KeyCode GetKeyCode() const { return m_KeyCode; }

		EVENT_CLASS_CATEGORY(EventCategoryKeyBoard | EventCategoryInput)

	protected:
		KeyEvent(KeyCode keycode) 
			:m_KeyCode(keycode) {}

		KeyCode m_KeyCode;
	};

	

	class BHive_API KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(KeyCode keycode, int repeatCount)
			:KeyEvent(keycode), m_RepeatCount(repeatCount) {}

		inline int GetRepeatCount() const { return m_RepeatCount; }

		BString ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << (int32_t)m_KeyCode << "(" << m_RepeatCount << " repeats)";
			return ss.str().c_str();
		}

		EVENT_CLASS_TYPE(KeyPressed)

	private:
		int m_RepeatCount;
	};

	class BHive_API KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(KeyCode keycode)
			:KeyEvent(keycode) {}

		BString ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << (int32_t)m_KeyCode;
			return ss.str().c_str();
		}

		EVENT_CLASS_TYPE(KeyReleased)
	};

	class BHive_API KeyTypedEvent : public KeyEvent
	{
	public:
		KeyTypedEvent(KeyCode keycode)
			:KeyEvent(keycode) {}


		BString ToString() const override
		{
			std::stringstream ss;
			ss << "KeyTypedEvent: " << (int32_t)m_KeyCode;
			return ss.str().c_str();
		}

		EVENT_CLASS_TYPE(KeyTyped)
	};
}
