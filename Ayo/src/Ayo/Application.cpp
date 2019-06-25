#include "ayopch.h"

#include "Application.h"

#include "Ayo/Input.h"

#include <glad/glad.h>

#include "Ayo/Renderer/Buffer.h"
#include "Ayo/Renderer/RenderCommand.h"
#include "Ayo/Renderer/Renderer.h"

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

		// example: setting up drawing a triangle and a square

		// Setup buffers
		std::shared_ptr<VertexBuffer> vertexBufferTriangle;
		std::shared_ptr<IndexBuffer> indexBufferTriangle;

		m_VertexArrayTriangle = VertexArray::Create();

		/* Vertices */
		float vertices[3 * 7] =
		{
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
			0.0f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
		};

		vertexBufferTriangle = VertexBuffer::Create(vertices, sizeof(vertices));

		/* Layout */
		BufferLayout layout = {
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float4, "a_Color"}
		};

		vertexBufferTriangle->SetLayout(layout);

		/* Indices */
		unsigned int indices[3] = { 0, 1, 2 };
		indexBufferTriangle = IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));

		/* Final Binding to VertexArray */
		m_VertexArrayTriangle->AddVertexBuffer(vertexBufferTriangle);
		m_VertexArrayTriangle->SetIndexBuffer(indexBufferTriangle);

		/* Setup Vertex Array of a Rectangle */
		std::shared_ptr<VertexBuffer> vertexBufferRect;
		std::shared_ptr<IndexBuffer> indexBufferRect;

		float rectVertices[4 * 3] =
		{
			-0.75f, -0.75f, 0.0f,
			0.75f, -0.75f, 0.0f,
			0.75f, 0.75f, 0.0f,
			-0.75f, 0.75f, 0.0f,
		};
		vertexBufferRect = VertexBuffer::Create(rectVertices, sizeof(rectVertices));

		vertexBufferRect->SetLayout(
			{ {ShaderDataType::Float3, "a_Position" } }
		);

		uint32_t rectIndices[2 * 3] = {
			0, 1, 3,
			3, 1, 2
		};
		indexBufferRect = IndexBuffer::Create(rectIndices, sizeof(rectIndices) / sizeof(uint32_t));

		m_VertexArraySquare = VertexArray::Create();
		m_VertexArraySquare->AddVertexBuffer(vertexBufferRect);
		m_VertexArraySquare->SetIndexBuffer(indexBufferRect);

		/* Shaders */
		std::string vertexSource = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			out vec3 v_Position;
			out vec4 v_Color;

			void main() {
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = vec4(a_Position, 1.0);
			}
		)";

		std::string fragmentSource = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;

			void main() {
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}
		)";

		// shader
		m_Shader.reset(new Shader(vertexSource, fragmentSource));

		/* Shaders */
		std::string vertexSourceFlat = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;

			out vec3 v_Position;

			void main() {
				v_Position = a_Position;
				gl_Position = vec4(a_Position, 1.0);
			}
		)";

		std::string fragmentSourceFlat = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;

			void main() {
				color = vec4(0.7, 0.3, 0.2, 1.0);
			}
		)";

		// shader
		m_FlatShader.reset(new Shader(vertexSourceFlat, fragmentSourceFlat));

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
		while (m_Running) {
			RenderCommand::SetClearColor({ 0.95f, 0.0625f, 0.93f, 1.0f });
			RenderCommand::Clear();

			Renderer::BeginScene();

			m_FlatShader->Bind();
			m_VertexArraySquare->Bind();
			Renderer::Submit(m_VertexArraySquare);

			m_Shader->Bind();
			m_VertexArrayTriangle->Bind();
			Renderer::Submit(m_VertexArrayTriangle);

			Renderer::EndScene();

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
