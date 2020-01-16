#include <Ayo.h>

#include "ImGui/imgui.h"

#include "AppSettings.h"

#include "Platform/OpenGL/OpenGLShader.h" // todo: remove/refactor
#include "Platform/OpenGL/OpenGLTexture.h"

class ExampleLayer : public Ayo::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
		SetupExampleScene();
	}

	void SetupExampleScene()
	{
		// example: setting up drawing a triangle and a square

		// Setup Camera
		m_Camera = std::make_shared<Ayo::Camera>();
		m_Camera->SetProjectionMatrix(glm::perspective(glm::radians(45.0f), 16.0f / 9.0f, 0.1f, 100.0f));
		m_Camera->SetViewMatrix(glm::identity<glm::mat4>());

		// Setup buffers
		std::shared_ptr<Ayo::VertexBuffer> vertexBufferTriangle;
		std::shared_ptr<Ayo::IndexBuffer> indexBufferTriangle;

		m_VertexArrayTriangle = Ayo::VertexArray::Create();

		/* Vertices */
		float vertices[3 * 9] =
		{
            // positions            // colors                   
			-0.5f, -0.5f, 0.0f,     1.0f, 0.0f, 0.0f, 1.0f,     0.0f, 0.0f,
			0.5f, -0.5f, 0.0f,      0.0f, 1.0f, 0.0f, 1.0f,     1.0f, 0.0f,
			0.0f, 0.5f, 0.0f,       0.0f, 1.0f, 1.0f, 1.0f,     0.5f, 1.0f
		};

		vertexBufferTriangle = Ayo::VertexBuffer::Create(vertices, sizeof(vertices));

		/* Layout */
		Ayo::BufferLayout layout = {
			{ Ayo::ShaderDataType::Float3, "a_Position" },
			{ Ayo::ShaderDataType::Float4, "a_Color"},
            { Ayo::ShaderDataType::Float2, "a_TexCoord"}
		};

		vertexBufferTriangle->SetLayout(layout);

		/* Indices */
		unsigned int indices[3] = { 0, 1, 2 };
		indexBufferTriangle = Ayo::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));

		/* Final Binding to VertexArray */
		m_VertexArrayTriangle->AddVertexBuffer(vertexBufferTriangle);
		m_VertexArrayTriangle->SetIndexBuffer(indexBufferTriangle);

		/* Setup Vertex Array of a Rectangle */
		std::shared_ptr<Ayo::VertexBuffer> vertexBufferRect;
		std::shared_ptr<Ayo::IndexBuffer> indexBufferRect;

		float rectVertices[4 * 3] =
		{
			-0.75f, -0.75f, 0.0f,
			0.75f, -0.75f, 0.0f,
			0.75f, 0.75f, 0.0f,
			-0.75f, 0.75f, 0.0f,
		};
		vertexBufferRect = Ayo::VertexBuffer::Create(rectVertices, sizeof(rectVertices));

		vertexBufferRect->SetLayout(
			{ {Ayo::ShaderDataType::Float3, "a_Position" } }
		);

		uint32_t rectIndices[2 * 3] = {
			0, 1, 3,
			3, 1, 2
		};
		indexBufferRect = Ayo::IndexBuffer::Create(rectIndices, sizeof(rectIndices) / sizeof(uint32_t));

		m_VertexArraySquare = Ayo::VertexArray::Create();
		m_VertexArraySquare->AddVertexBuffer(vertexBufferRect);
		m_VertexArraySquare->SetIndexBuffer(indexBufferRect);

		/* Shaders */
		// todo: remember to add in model matrix
		std::string vertexSourcePath = AppSettings::DEBUG_ROOT_PATH + "/posColTex.vs";

		std::string fragmentSourcePath = AppSettings::DEBUG_ROOT_PATH + "/texture.fs";

		// shader
		m_Shader = Ayo::Shader::CreateFromPath(vertexSourcePath, fragmentSourcePath);

        // Textures
        std::string texturePath = AppSettings::DEBUG_ROOT_PATH + "/wall.jpg";

        m_Texture = Ayo::Texture::Create(texturePath);

		/* Shaders */
		std::string vertexSourceFlat = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjectionMatrix;

			out vec3 v_Position;

			void main() {
				v_Position = a_Position;
				gl_Position = u_ViewProjectionMatrix * vec4(a_Position, 1.0);
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
		m_FlatShader = Ayo::Shader::Create(vertexSourceFlat, fragmentSourceFlat);

		m_Camera->SetPosition(glm::vec3(0.0f, 0.0f, 3.0f));
	}

	void OnUpdate() override
	{
		//AYO_INFO("ExampleLayer::Update");

		if (Ayo::Input::IsKeyPressed(AYO_KEY_LEFT)) {
			m_Camera->SetPosition(glm::vec3(m_Camera->GetPosition().x - speed, m_Camera->GetPosition().y, m_Camera->GetPosition().z));
		}
		else if (Ayo::Input::IsKeyPressed(AYO_KEY_RIGHT)) {
			m_Camera->SetPosition(glm::vec3(m_Camera->GetPosition().x + speed, m_Camera->GetPosition().y, m_Camera->GetPosition().z));
		}

        if (Ayo::Input::IsKeyPressed(AYO_KEY_W)) {
            m_WireframeMode = !m_WireframeMode;
            Ayo::RenderCommand::SetWireframeMode(m_WireframeMode);
        }

		if (Ayo::Input::IsKeyPressed(AYO_KEY_UP)) {
			m_Camera->SetPosition(glm::vec3(m_Camera->GetPosition().x, m_Camera->GetPosition().y, m_Camera->GetPosition().z - speed));
		}
		else if (Ayo::Input::IsKeyPressed(AYO_KEY_DOWN)) {
			m_Camera->SetPosition(glm::vec3(m_Camera->GetPosition().x, m_Camera->GetPosition().y, m_Camera->GetPosition().z + speed));
		}

		if (Ayo::Input::IsKeyPressed(AYO_KEY_Q)) {
			m_Camera->Rotate(rotSpeed, m_Camera->GetForwardVector());
		}
		else if (Ayo::Input::IsKeyPressed(AYO_KEY_E)) {
			m_Camera->Rotate(-rotSpeed, m_Camera->GetForwardVector());
		}

		Ayo::RenderCommand::SetClearColor({ 0.95f, 0.0625f, 0.93f, 1.0f });
		Ayo::RenderCommand::Clear();

		Ayo::Renderer::BeginScene();

		//m_FlatShader->Bind();
        //std::dynamic_pointer_cast<Ayo::OpenGLShader>(m_FlatShader)->UpdateMat4Uniform("u_ViewProjectionMatrix", m_Camera->GetViewProjectionMatrix());
        
		//m_VertexArraySquare->Bind();
		//Ayo::Renderer::Submit(m_VertexArraySquare);

		m_Shader->Bind();
		std::dynamic_pointer_cast<Ayo::OpenGLShader>(m_Shader)->UpdateMat4Uniform("u_ViewProjectionMatrix", m_Camera->GetViewProjectionMatrix());
        // texture
        std::dynamic_pointer_cast<Ayo::OpenGLShader>(m_Shader)->UpdateIntUniform("u_Texture", 0);
        m_Texture->Bind(0);

		m_VertexArrayTriangle->Bind();
		Ayo::Renderer::Submit(m_VertexArrayTriangle);

		Ayo::Renderer::EndScene();

	}

	void OnEvent(Ayo::Event& e) override
	{
		//AYO_TRACE("{0}", e);
	}

	virtual void OnImGuiDraw() override
	{
		ImGui::Begin("Test");
		ImGui::Text("Hello world");
		ImGui::End();
	}

private:

	// buffers
	std::shared_ptr<Ayo::VertexArray> m_VertexArrayTriangle;
	std::shared_ptr<Ayo::VertexArray> m_VertexArraySquare;

	// temporary, as example.
	std::shared_ptr<Ayo::Shader> m_Shader;
	std::shared_ptr<Ayo::Shader> m_FlatShader;

    std::shared_ptr<Ayo::Texture> m_Texture;

	std::shared_ptr<Ayo::Camera> m_Camera;

	float speed = 0.01f;
	float rotSpeed = 0.1f;

    bool m_WireframeMode = false;
};

class Sandbox : public Ayo::Application
{
	public:
		Sandbox()
		{
			PushLayer(new ExampleLayer());
		}

		~Sandbox()
		{

		}
};

Ayo::Application* Ayo::CreateApplication()
{
	return new Sandbox();
}