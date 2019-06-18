#pragma once

#include "Core.h"
#include "Ayo/Events/Event.h"
#include "Ayo/Events/ApplicationEvent.h"
#include "Window.h"
#include "Ayo/Layer.h"
#include "Ayo/LayerStack.h"

#include "Ayo/ImGui/ImGuiLayer.h"
#include "Ayo/Renderer/Shader.h"

namespace Ayo {

	class VertexBuffer;
	class IndexBuffer;

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

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }

	private:
		bool OnWindowClose(AppWindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;

		void OnEvent(Event& e);

		LayerStack m_LayerStack;

		static Application* s_Instance;

		// buffers
		unsigned int m_VertexArray;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;

		// temporary, as example.
		std::unique_ptr<Shader> m_Shader;
	};

	// To be defined in CLIENT
	Application* CreateApplication();

}

