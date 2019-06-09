#include "ayopch.h"
#include "WindowsInput.h"

#include "Ayo/Application.h"
#include <GLFW/glfw3.h>

namespace Ayo {

	std::shared_ptr<Input> Input::s_Instance = std::shared_ptr<Input>(new WindowsInput());

	bool WindowsInput::IsKeyPressed_Implementation(int keycode)
	{
		GLFWwindow* window = (GLFWwindow*)(Ayo::Application::Get().GetWindow().GetNativeWindow());
		int state = glfwGetKey(window, keycode);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool WindowsInput::IsMouseButtonPressed_Implementation(int button)
	{
		GLFWwindow* window = (GLFWwindow*)(Ayo::Application::Get().GetWindow().GetNativeWindow());

		return glfwGetMouseButton(window, (int)button) == GLFW_PRESS;
	}

	float WindowsInput::GetMouseX_Implementation()
	{
		GLFWwindow* window = (GLFWwindow*)(Ayo::Application::Get().GetWindow().GetNativeWindow());
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		
		return (float)xpos;
	}

	float WindowsInput::GetMouseY_Implementation()
	{
		GLFWwindow* window = (GLFWwindow*)(Ayo::Application::Get().GetWindow().GetNativeWindow());
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);

		return (float)ypos;
	}

	std::pair<float, float> WindowsInput::GetMousePosition_Implementation()
	{
		GLFWwindow* window = (GLFWwindow*)(Ayo::Application::Get().GetWindow().GetNativeWindow());
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);

		return { (float)xpos, (float)ypos };
	}

	WindowsInput::WindowsInput()
	{

	}


	WindowsInput::~WindowsInput()
	{

	}
}
