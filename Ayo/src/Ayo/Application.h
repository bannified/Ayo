#pragma once

#include "Core.h"
#include "Ayo/Events/Event.h"
#include "Ayo/Events/ApplicationEvent.h"
#include "Window.h"

namespace Ayo {

	class AYO_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

	private:
		bool OnWindowClose(AppWindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;

		void OnEvent(Event& e);
	};

	// To be defined in CLIENT
	Application* CreateApplication();

}

