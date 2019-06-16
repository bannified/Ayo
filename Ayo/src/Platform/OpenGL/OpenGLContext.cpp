#include "ayopch.h"
#include "OpenGLContext.h"

namespace Ayo {

	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		AYO_CORE_ASSERT(windowHandle, "Window handle is null!");
	}

	OpenGLContext::~OpenGLContext()
	{
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);

		// glad
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		AYO_CORE_ASSERT(status, "Failed to initialize Glad!");

		// checking GPU driver
		AYO_INFO("GPU info: {0}, {1}, {2}", glGetString(GL_VENDOR), glGetString(GL_RENDERER), glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffer()
	{
		glfwSwapBuffers(m_WindowHandle);
	}

	void OpenGLContext::Shutdown()
	{
		if (m_WindowHandle) {
			glfwDestroyWindow(m_WindowHandle);
		}
		else {
			AYO_CORE_WARN("No Window to destroy upon Window shutting down.");
		}
	}

}
