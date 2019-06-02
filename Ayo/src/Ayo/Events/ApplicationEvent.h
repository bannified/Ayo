#pragma once

#include "Event.h"

#include <string>
#include <sstream>

namespace Ayo {

	class AYO_API AppTickEvent : public Event
	{
	public: 
		AppTickEvent() {}

		EVENT_CLASS_TYPE(AppTick)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class AYO_API AppUpdateEvent : public Event
	{
	public:
		AppUpdateEvent() {}

		EVENT_CLASS_TYPE(AppUpdate)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class AYO_API AppRenderEvent : public Event
	{
	public:
		AppRenderEvent() {}

		EVENT_CLASS_TYPE(AppRender)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class AYO_API AppWindowResizeEvent : public Event
	{
	public:
		AppWindowResizeEvent(int xSize, int ySize)
			: m_XSize(xSize), m_YSize(ySize) {}

		EVENT_CLASS_TYPE(AppWindowResize)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)

		inline int Get_XSize(){ return m_XSize; }
		inline int Get_YSize(){ return m_YSize; }

	private:
		unsigned int m_XSize; // width
		unsigned int m_YSize; // height
	};

	class AYO_API AppWindowCloseEvent : public Event
	{
	public:
		AppWindowCloseEvent() {}

		EVENT_CLASS_TYPE(AppWindowClose)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};


	// AppTick, AppUpdate, AppRender, AppWindowResize, AppWindowClose, AppWindowMinimize,
}
