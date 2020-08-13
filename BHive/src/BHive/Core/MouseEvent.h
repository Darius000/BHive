#pragma once

#include "Event.h"

namespace BHive
{
	class BHive_API MouseMovedEvent : public Event 
	{
	public:
		MouseMovedEvent(float x, float y)
			:m_MouseX(x), m_MouseY(y) {}

		inline float GetX() const { return m_MouseX; }
		inline float GetY() const { return m_MouseY; }

		BString ToString() const override
		{
			std::stringstream ss;
			ss << "MousedMovedEvent: " << m_MouseX << ", " << m_MouseY;
			return ss.str().c_str();
		}

		EVENT_CLASS_TYPE(MouseMoved)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

	private:
		float m_MouseX, m_MouseY;
	};

	class BHive_API MouseScrolledEvent : public Event
	{
	public:
		MouseScrolledEvent(float xOffset, float yOffset)
			:m_XOffset(xOffset), m_YOffset(yOffset) {}

		inline float GetXOffset() const { return m_XOffset; }
		inline float GetYOffset() const { return m_YOffset; }

		BString ToString() const override
		{
			std::stringstream ss;
			ss << "MousedScrolledEvent: " << GetXOffset() << ", " << GetYOffset();
			return ss.str().c_str();
		}

		EVENT_CLASS_TYPE(MouseScrolled)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

	private:
		float m_XOffset, m_YOffset;
	};

	class BHive_API MouseButtonEvent : public Event
	{
	public:
		inline MouseButton GetMouseButton() const { return m_Button; }

		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

	protected:
		MouseButtonEvent(MouseButton button)
			:m_Button(button) {}

		MouseButton m_Button;
	};

	class BHive_API MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(MouseButton button)
			:MouseButtonEvent(button) {}

		BString ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonPressedEvent: " << (int32_t)m_Button;
			return ss.str().c_str();
		}

		EVENT_CLASS_TYPE(MouseButtonPressed)
	};

	class BHive_API MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleasedEvent(MouseButton button)
			:MouseButtonEvent(button) {}

		BString ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonReleasedEvent: " << (int32_t)m_Button;
			return ss.str().c_str();
		}

		EVENT_CLASS_TYPE(MouseButtonReleased)
	};
}