#pragma once

#include "ayopch.h"

#include "Ayo/Core.h"
#include "Ayo/Window.h"
#include "Ayo/Events/Event.h"
#include "Ayo/Events/ApplicationEvent.h"
#include "Ayo/Events/KeyEvent.h"
#include "Ayo/Events/MouseEvent.h"

#include "GLFW/glfw3.h"

namespace Ayo {

	class AYO_API WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProperties& properties);
		virtual ~WindowsWindow();

		void OnUpdate() override;

		inline unsigned int GetWidth() const override { return m_WindowData.Width; };
		inline unsigned int GetHeight() const override { return m_WindowData.Height; };
		
		inline GLFWwindow* GetGLFWWindow() { return m_Window; }

		void SetVSync(bool enabled) override;
		bool IsVSync() const override;

		inline void SetEventCallback(const EventCallbackFunction& callback) override
		{
			m_WindowData.EventCallback = callback;
		};

	private:
		struct WindowData
		{
			std::string Title;

			unsigned int Width;
			unsigned int Height;

			bool Vsync;

			EventCallbackFunction EventCallback;
		};

		WindowData m_WindowData;

		GLFWwindow* m_Window;

		void Init(const WindowProperties& properties);

		void Shutdown();		
	};
}

