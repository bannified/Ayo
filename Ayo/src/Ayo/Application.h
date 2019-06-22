#pragma once

#include "Core.h"
#include "Ayo/Events/Event.h"
#include "Ayo/Events/ApplicationEvent.h"
#include "Window.h"
#include "Ayo/Layer.h"
#include "Ayo/LayerStack.h"

#include "Ayo/ImGui/ImGuiLayer.h"
#include "Ayo/Renderer/Shader.h"

#include "Ayo/Renderer/VertexArray.h"

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
		std::shared_ptr<VertexArray> m_VertexArrayTriangle;
		std::shared_ptr<VertexArray> m_VertexArraySquare;

		// temporary, as example.
		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<Shader> m_FlatShader;
	};

	// To be defined in CLIENT
	Application* CreateApplication();

}

