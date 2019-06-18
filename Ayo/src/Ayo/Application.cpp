#include "ayopch.h"

#include "Application.h"

#include "Ayo/Input.h"

#include <glad/glad.h>

#include "Ayo/Renderer/Buffer.h"

namespace Ayo {

	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		AYO_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create(WindowProperties("Ayo\'s first window!", 1280, 720)));
		
		// This functor-like object can be called, and get forwarded to this Application object's OnEvent method, where the events are handled.
		auto functor = BIND_EVENT_FUNCTION(Application::OnEvent); 
		m_Window->SetEventCallback(functor);

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

		// example: setting up drawing a triangle

		// setup vertice arrays
		glGenVertexArrays(1, &m_VertexArray);
		glBindVertexArray(m_VertexArray);

		float vertices[3 * 3] =
		{
			-0.5f, -0.5f, 0.0f,
			0.5f, -0.5f, 0.0f,
			0.0f, 0.5f, 0.0f
		};

		m_VertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
		m_VertexBuffer->Bind();

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

		unsigned int indices[3] = { 0, 1, 2 };
		m_IndexBuffer.reset(IndexBuffer::Create(indices, 3));
		m_IndexBuffer->Bind();
		
		std::string vertexSource = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;

			out vec3 v_Position;

			void main() {
				v_Position = a_Position;
				gl_Position = vec4(a_Position, 1.0);
			}
		)";

		std::string fragmentSource = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;

			void main() {
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
			}
		)";

		// shader
		m_Shader.reset(new Shader(vertexSource, fragmentSource));
	}


	Application::~Application()
	{
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		
		// If event is AppWindowCloseEvent, call OnWindowClose.
		dispatcher.Dispatch<AppWindowCloseEvent>(BIND_EVENT_FUNCTION(Application::OnWindowClose));

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
			glClearColor(0.0f, 0.0f, 1.0f, 1);
			glClear(GL_COLOR_BUFFER_BIT);


			m_Shader->Bind();
			// drawing a triangle
			glBindVertexArray(m_VertexArray);
			glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

			//

			// from the bottom of the stack.
			for (Layer* layer : m_LayerStack) {
				layer->OnUpdate();
			}
			
			/* Draw ImGui */
			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack) {
				layer->OnImGuiDraw();
			}
			m_ImGuiLayer->End();

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
