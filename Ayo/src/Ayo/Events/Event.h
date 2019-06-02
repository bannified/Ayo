#pragma once

#include "Ayo/Core.h"

namespace Ayo {

	enum class EventType
	{
		KeyPressedEvent, KeyReleasedEvent,
		MouseButtonPressed, MouseButtonReleased, MouseWheelScrolled, MouseMoved,
		AppTick, AppUpdate, AppRender, AppWindowResize, AppWindowClose, AppWindowMinimize,
	};

	enum EventCategory
	{
		None = 0,
		EventCategoryApplication = SINGLE_BIT(0),
		EventCategoryInput = SINGLE_BIT(1),
		EventCategoryMouse = SINGLE_BIT(2),
		EventCategoryMouseButton = SINGLE_BIT(3),
		EventCategoryKeyboard = SINGLE_BIT(4)
	};

#define EVENT_CLASS_TYPE(eventType) static EventType GetStaticType() { return EventType::##eventType; } \
										virtual EventType GetEventType() const override { return GetStaticType(); } \
										virtual const char* GetName() const override { return #eventType; } \

#define EVENT_CLASS_CATEGORY(eventCategory) virtual int GetCategoryFlags() const { return eventCategory; }

	class AYO_API Event
	{
	public:
		bool b_Handled = false;

		/* Event Type */
		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual std::string ToString() const
		{
			return GetName();
		};

		/* Event Category */
		virtual int GetCategoryFlags() const = 0;		

		inline bool IsInCategory(EventCategory category)
		{
			return GetCategoryFlags() & category;
		}
	};

	class EventDispatcher
	{
		template<typename T>
		using EventFunction = std::function<bool(T&)>; // function returning bool.

	public:
		EventDispatcher(Event& event)
			: m_Event(event) {}

		template<typename T>
		bool Dispatch(EventFunction<T> func)
		{
			if (m_Event.GetEventType() == T::GetStaticType())
			{
				m_Event.b_Handled = func(*(T*)&m_Event); // Converting Event& to T&
				return true;
			}
			return false;
		}

	private:
		Event& m_Event;
	};

	inline std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		return os << e.ToString();
	}
}

