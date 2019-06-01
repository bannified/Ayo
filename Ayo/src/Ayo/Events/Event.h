#pragma once

#include "Ayo/Core.h"

#include <string>

namespace Ayo {

	enum class EventType
	{
		KeyPressedEvent, KeyReleasedEvent,
		MouseButtonPress, MouseButtonRelease, MouseWheelScroll, MouseMove,
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

	class AYO_API Event
	{
	public:
		bool b_Handled = false;

		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;

		virtual std::string ToString() const { return GetName(); };

		inline bool IsInCategory(EventCategory category)
		{
			return GetCategoryFlags() & category;
		}
	};
}

