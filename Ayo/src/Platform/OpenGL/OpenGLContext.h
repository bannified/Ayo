#pragma once
#include "Ayo/Renderer/GraphicsContext.h"
#include "glfw/glfw3.h"
#include "glad/glad.h"

struct GLFWwindow;

namespace Ayo {

	class AYO_API OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* windowHandle);

		virtual ~OpenGLContext();

		virtual void Init() override;
		virtual void SwapBuffer() override;
		virtual void Shutdown() override;

	private:
		GLFWwindow* m_WindowHandle;
	};

}

