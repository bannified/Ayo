#pragma once

#include "Event.h"

namespace Ayo 
{
	class AYO_API KeyEvent : public Event
	{
	public:
		inline int GetKeyCode() { return m_KeyCode; }

	protected:
		KeyEvent(int keycode)
			: m_KeyCode(keycode) {}

		EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryKeyboard)

		int m_KeyCode;
	};

	class AYO_API KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(int keycode, int repeatCount)
			: KeyEvent(keycode), m_RepeatCount(repeatCount) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << m_KeyCode << ", RepeatCount: " << m_RepeatCount;
			return ss.str();
		}

		inline int GetRepeatCount() { return m_RepeatCount; }

		EVENT_CLASS_TYPE(KeyPressed)

	private:
		int m_RepeatCount;
	};

	class AYO_API KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(int keycode)
			: KeyEvent(keycode) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << m_KeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased)
	};

	class AYO_API KeyTypedEvent : public KeyEvent
	{
	public:
		KeyTypedEvent(int keycode)
			: KeyEvent(keycode)
		{
		}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyTypedEvent: " << m_KeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyTyped)
	};
}