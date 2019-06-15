#include "ayopch.h"

#include "WindowsWindow.h"
#include "WindowsInput.h"
#include "glad/glad.h"

namespace Ayo {

	static bool isGLFWInitialized = false;

	static void GLFWErrorCallback(int error, const char* description)
	{
		AYO_CORE_ERROR("GLFW Error {0}: {1}", error, description);
	};

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

			glfwSetErrorCallback(GLFWErrorCallback);
			isGLFWInitialized = true;
		}

		m_Window = glfwCreateWindow(properties.Width, properties.Height, properties.Title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_Window);

		// glad
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		AYO_CORE_ASSERT(status, "Failed to initialize Glad!");

		glfwSetWindowUserPointer(m_Window, &m_WindowData);
		SetVSync(true);

		// Setting GLFW callbacks.

		/* --- Window Callbacks --- */
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
		{
			WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);
			data->Width = width;
			data->Height = height;
			
			AppWindowResizeEvent e(width, height);
			data->EventCallback(e);
		});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
		{
			WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);
			
			AppWindowCloseEvent e;
			data->EventCallback(e);
		});
		/* ------------------------- */
		
		/* --- Mouse Callbacks --- */

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
		{
			WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);

			// TODO: Add in mods to int Events.
			switch (action) {
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent e(button);
					data->EventCallback(e);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent e(button);
					data->EventCallback(e);
					break;
				}					
			}

		});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double x, double y)
		{
			WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);

			MouseMovedEvent e((float)x, (float)y);
			data->EventCallback(e);
		});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset)
		{
			WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);

			MouseScrolledEvent e((float)xOffset, (float)yOffset);
			data->EventCallback(e);
		});

		/* ----------------------- */

		/* --- Key Callbacks --- */

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);

			// TODO: Add in mods to Key Events.
			switch (action) {
				case GLFW_PRESS:
				{
					KeyPressedEvent e(key, 0);
					data->EventCallback(e);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleasedEvent e(key);
					data->EventCallback(e);
					break;
				}
				case GLFW_REPEAT:
				{
					KeyPressedEvent e(key, 1); //TODO: Extract key repeat count.
					data->EventCallback(e);
					break;
				}
			}
		});

		glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int keycode)
		{
			WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);
			KeyTypedEvent e(keycode);

			data->EventCallback(e);
		});

		/* -------------------------- */

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
