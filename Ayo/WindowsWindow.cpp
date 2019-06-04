#include "ayopch.h"
#include "WindowsWindow.h"

namespace Ayo {

	static bool isGLFWInitialized = false;

	Window* Window::Create(const WindowProperties& properties)
	{
		return new WindowsWindow(properties);
	}

	WindowsWindow::WindowsWindow(const WindowProperties& properties)
	{
		Init(properties);
	}

	WindowsWindow::~WindowsWindow()
	{
		Shutdown();
	}

	void WindowsWindow::OnUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}

	void WindowsWindow::SetVSync(bool enabled)
	{
		if (enabled)
		{
			glfwSwapInterval(1);
		} else
		{
			glfwSwapInterval(0);
		}

		m_WindowData.Vsync = enabled;
	}

	bool WindowsWindow::IsVSync() const
	{
		return m_WindowData.Vsync;
	}

	void WindowsWindow::Init(const WindowProperties& properties)
	{
		m_WindowData.Width = properties.Width;
		m_WindowData.Height = properties.Height;
		m_WindowData.Title = properties.Title;

		AYO_CORE_INFO("Creating a window: {0}, {1}x{2}.", m_WindowData.Title, m_WindowData.Width, m_WindowData.Height);

		if (!isGLFWInitialized)
		{
			int success = glfwInit();
			AYO_ASSERT(success, "Could not initialize GLFW");

			isGLFWInitialized = true;
		}

		m_Window = glfwCreateWindow(properties.Width, properties.Height, properties.Title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_Window);
		glfwSetWindowUserPointer(m_Window, &m_WindowData);
		SetVSync(true);
	}

	void Ayo::WindowsWindow::Shutdown()
	{
		if (m_Window)
		{
			glfwDestroyWindow(m_Window);
		} else {
			AYO_CORE_WARN("No Window to destroy upon Window shutting down.");
		}
	}
}
