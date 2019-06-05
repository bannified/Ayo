#include "ayopch.h"

#include "Application.h"

namespace Ayo {

#define BIND_EVENT_FUNCTION(x) std::bind(&x, this, std::placeholders::_1)

	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create(WindowProperties("Ayo\'s first window!", 1280, 720)));
		
		// This functor-like object can be called, and get forwarded to this Application object's OnEvent method, where the events are handled.
		auto functor = BIND_EVENT_FUNCTION(Application::OnEvent); 
		m_Window->SetEventCallback(functor);
	}


	Application::~Application()
	{
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		
		// If event is AppWindowCloseEvent, call OnWindowClose.
		dispatcher.Dispatch<AppWindowCloseEvent>(BIND_EVENT_FUNCTION(Application::OnWindowClose));

		AYO_CORE_TRACE("{0}", e);

		// From top of the stack.
		for (auto rit = m_LayerStack.rbegin(); rit != m_LayerStack.rend(); ++rit) {
			(*rit)->OnEvent(e);

			if (e.b_Handled)
			{
				break; // stop propagating further once handled.
			}
		}

		
	}

	void Application::Run()
	{
		while (m_Running) 
		{
			// from the bottom of the stack.
			for (Layer* layer : m_LayerStack) {
				layer->OnUpdate();
			}

			m_Window->OnUpdate();
		}
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* overlay)
	{
		m_LayerStack.PushOverlay(overlay);
	}

	void Application::RemoveLayer(Layer* layer)
	{
		m_LayerStack.RemoveLayer(layer);
	}

	void Application::RemoveOverlay(Layer* overlay)
	{
		m_LayerStack.RemoveOverlay(overlay);
	}

	bool Application::OnWindowClose(AppWindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

	

}
