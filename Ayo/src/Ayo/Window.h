#pragma once

#include "ayopch.h"

#include "Core.h"
#include "Events/Event.h"

namespace Ayo {

	struct WindowProperties
	{
		std::string Title;

		unsigned int Width;
		unsigned int Height;

	public:
		WindowProperties(const std::string title = "Ayo Engine",
						 unsigned int width = 1280,
						 unsigned int height = 720)
			: Title(title), Width(width), Height(height)
		{
		}
	};

	// Abstract representation of a window. 
	// Meant to be an interface implemented different rendering APIs by to enable cross-platform support.
	class AYO_API Window
	{
	public:
		using EventCallbackFunction = std::function<void(Event&)>;

		virtual ~Window() { };

		virtual void OnUpdate() = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		virtual void SetEventCallback(const EventCallbackFunction& callback) = 0;

		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		static Window* Create(const WindowProperties& properties = WindowProperties());
	};	
}