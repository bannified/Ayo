#pragma once

#include "Core.h"
#include "Ayo/Events/Event.h"
#include "Ayo/Events/ApplicationEvent.h"
#include "Window.h"
#include "Ayo/Layer.h"
#include "Ayo/LayerStack.h"

namespace Ayo {

	class AYO_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		/* LayerStack Operations */
		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		void RemoveLayer(Layer* layer);
		void RemoveOverlay(Layer* overlay);

	private:
		bool OnWindowClose(AppWindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;

		void OnEvent(Event& e);

		LayerStack m_LayerStack;
	};

	// To be defined in CLIENT
	Application* CreateApplication();

}

