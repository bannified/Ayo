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
		std::shared_ptr<Ayo::VertexBuffer> vertexBufferCube;
		std::shared_ptr<Ayo::IndexBuffer> indexBufferCube;

		m_VertexArrayCube = Ayo::VertexArray::Create();

		/* Vertices */
        float vertices[] = {
            // Vertices             // Tex coords
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
             0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
             0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,

            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
             0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
             0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
            -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,

            -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

             0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
             0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
             0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
             0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
             0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
             0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
             0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
             0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  0.0f, 0.0f
        };

		vertexBufferCube = Ayo::VertexBuffer::Create(vertices, sizeof(vertices));

		/* Layout */
		Ayo::BufferLayout layout = {
			{ Ayo::ShaderDataType::Float3, "a_Position"},
            { Ayo::ShaderDataType::Float2, "a_TexCoord"}
		};

		vertexBufferCube->SetLayout(layout);

		/* Indices */
		unsigned int indices[] = {  0,  1,      2,      2,      3,      0,
                                    4,  4 + 1,  4 + 2,  4 + 2,  4 + 3,  4,
                                    8,  8 + 1,  8 + 2,  8 + 2,  8 + 3,  8,
                                    12, 12 + 1, 12 + 2, 12 + 2, 12 + 3, 12,
                                    16, 16 + 1, 16 + 2, 16 + 2, 16 + 3, 16,
                                    20, 20 + 1, 20 + 2, 20 + 2, 20 + 3, 20,
        };
		indexBufferCube = Ayo::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));

		/* Final Binding to VertexArray */
		m_VertexArrayCube->AddVertexBuffer(vertexBufferCube);
		m_VertexArrayCube->SetIndexBuffer(indexBufferCube);

		/* Shaders */
		// todo: remember to add in model matrix
		std::string vertexSourcePath = AppSettings::DEBUG_ROOT_PATH + "/posTex.vs";

		std::string fragmentSourcePath = AppSettings::DEBUG_ROOT_PATH + "/texture.fs";

		// shader
		m_Shader = Ayo::Shader::CreateFromPath(vertexSourcePath, fragmentSourcePath);

        // Textures
        std::string texturePath = AppSettings::DEBUG_ROOT_PATH + "/container.jpg";

        m_Texture = Ayo::Texture::Create(texturePath);

		m_Camera->SetPosition(glm::vec3(0.0f, 0.0f, 3.0f));

        modelTransform = glm::mat4(1.0f);
	}

	void OnUpdate() override
	{
		//AYO_INFO("ExampleLayer::Update");

        // horizontal movement of camera
		if (Ayo::Input::IsKeyPressed(AYO_KEY_LEFT)) {
			m_Camera->SetPosition(glm::vec3(m_Camera->GetPosition().x - speed, m_Camera->GetPosition().y, m_Camera->GetPosition().z));
		}
		else if (Ayo::Input::IsKeyPressed(AYO_KEY_RIGHT)) {
			m_Camera->SetPosition(glm::vec3(m_Camera->GetPosition().x + speed, m_Camera->GetPosition().y, m_Camera->GetPosition().z));
		}

        // in/out movement of camera
        if (Ayo::Input::IsKeyPressed(AYO_KEY_UP)) {
            m_Camera->SetPosition(glm::vec3(m_Camera->GetPosition().x, m_Camera->GetPosition().y, m_Camera->GetPosition().z - speed));
        }
        else if (Ayo::Input::IsKeyPressed(AYO_KEY_DOWN)) {
            m_Camera->SetPosition(glm::vec3(m_Camera->GetPosition().x, m_Camera->GetPosition().y, m_Camera->GetPosition().z + speed));
        }

        // vertical movement of camera
        if (Ayo::Input::IsKeyPressed(AYO_KEY_SPACE)) {
            m_Camera->SetPosition(glm::vec3(m_Camera->GetPosition().x, m_Camera->GetPosition().y + speed, m_Camera->GetPosition().z));
        }
        else if (Ayo::Input::IsKeyPressed(AYO_KEY_LEFT_CONTROL)) {
            m_Camera->SetPosition(glm::vec3(m_Camera->GetPosition().x, m_Camera->GetPosition().y - speed, m_Camera->GetPosition().z));
        }

        // yaw modification of camera
        if (Ayo::Input::IsKeyPressed(AYO_KEY_Z)) {
            m_Camera->Rotate(rotSpeed * 0.1, glm::vec3(0.0f, 1.0f, 0.0f));
        }
        else if (Ayo::Input::IsKeyPressed(AYO_KEY_C)) {
            m_Camera->Rotate(-rotSpeed * 0.1, glm::vec3(0.0f, 1.0f, 0.0f));
        }

        // pitch modification of camera
        if (Ayo::Input::IsKeyPressed(AYO_KEY_EQUAL)) {
            m_Camera->Rotate(rotSpeed * 0.1, glm::vec3(1.0f, 0.0f, 0.0f));
        }
        else if (Ayo::Input::IsKeyPressed(AYO_KEY_MINUS)) {
            m_Camera->Rotate(-rotSpeed * 0.1, glm::vec3(1.0f, 0.0f, 0.0f));
        }

        if (Ayo::Input::IsKeyPressed(AYO_KEY_1)) {
            m_WireframeMode = !m_WireframeMode;
            Ayo::RenderCommand::SetWireframeMode(m_WireframeMode);
        }

        // Vertical movement of cube
        if (Ayo::Input::IsKeyPressed(AYO_KEY_W)) {
            modelTransform = glm::translate(modelTransform, glm::vec3(0.0f, speed, 0.0f));
        } else if (Ayo::Input::IsKeyPressed(AYO_KEY_S))
        {
            modelTransform = glm::translate(modelTransform, glm::vec3(0.0f, -speed, 0.0f));
        }

        // horizontal movement of cube
        if (Ayo::Input::IsKeyPressed(AYO_KEY_A)) {
            modelTransform = glm::translate(modelTransform, glm::vec3(speed, 0.0f, 0.0f));
        }
        else if (Ayo::Input::IsKeyPressed(AYO_KEY_D)) {
            modelTransform = glm::translate(modelTransform, glm::vec3(-speed, 0.0f, 0.0f));
        }

        // Changing the object's yaw
		if (Ayo::Input::IsKeyPressed(AYO_KEY_Q)) {
			//m_Camera->Rotate(rotSpeed, m_Camera->GetForwardVector());
            modelTransform = glm::rotate(modelTransform, glm::radians(-rotSpeed), glm::vec3(0.0f, 1.0f, 0.0f));
		}
		else if (Ayo::Input::IsKeyPressed(AYO_KEY_E)) {
			//m_Camera->Rotate(-rotSpeed, m_Camera->GetForwardVector());
            modelTransform = glm::rotate(modelTransform, glm::radians(rotSpeed), glm::vec3(0.0f, 1.0f, 0.0f));
		}

        // Changing the object's pitch
        if (Ayo::Input::IsKeyPressed(AYO_KEY_R)) {
            //m_Camera->Rotate(rotSpeed, m_Camera->GetForwardVector());
            modelTransform = glm::rotate(modelTransform, glm::radians(rotSpeed), glm::vec3(1.0f, 0.0f, 0.0f));
        }
        else if (Ayo::Input::IsKeyPressed(AYO_KEY_F)) {
            //m_Camera->Rotate(-rotSpeed, m_Camera->GetForwardVector());
            modelTransform = glm::rotate(modelTransform, glm::radians(-rotSpeed), glm::vec3(1.0f, 0.0f, 0.0f));
        }

		Ayo::RenderCommand::SetClearColor({ 0.95f, 0.0625f, 0.93f, 1.0f });
		Ayo::RenderCommand::Clear();

		Ayo::Renderer::BeginScene();

		m_Shader->Bind();
		std::dynamic_pointer_cast<Ayo::OpenGLShader>(m_Shader)->UpdateMat4Uniform("u_ViewProjectionMatrix", m_Camera->GetViewProjectionMatrix() * modelTransform);
        // texture
        std::dynamic_pointer_cast<Ayo::OpenGLShader>(m_Shader)->UpdateIntUniform("u_Texture", 0);
        m_Texture->Bind(0);

		m_VertexArrayCube->Bind();
		Ayo::Renderer::Submit(m_VertexArrayCube);

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
	std::shared_ptr<Ayo::VertexArray> m_VertexArrayCube;

	// temporary, as example.
    glm::mat4 modelTransform;

	std::shared_ptr<Ayo::Shader> m_Shader;

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