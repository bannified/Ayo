#include "ayopch.h"

#include "Application.h"

namespace Ayo {

	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create(WindowProperties("Ayo\'s first window!", 1280, 720)));
	}


	Application::~Application()
	{
	}

	void Application::Run()
	{
		while (m_Running) 
		{
			m_Window->OnUpdate();
		}
	}
}
