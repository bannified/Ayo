#include <Ayo.h>

#include "ImGui/imgui.h"

#include "AppSettings.h"

class ExampleLayer : public Ayo::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
		SetupExampleScene();
        Ayo::Time::Initialize();
	}

	void SetupExampleScene()
	{
		// example: setting up drawing a triangle and a square

		// Setup Camera
		m_Camera = std::make_shared<Ayo::Camera>();
		m_Camera->SetProjectionMatrix(glm::perspective(glm::radians(45.0f), 16.0f / 9.0f, 0.1f, 100.0f));
		//m_Camera->SetViewMatrix(glm::identity<glm::mat4>());

        modelTransform = glm::mat4(1.0f);

		// Setup buffers
		std::shared_ptr<Ayo::VertexBuffer> vertexBufferCube;
		std::shared_ptr<Ayo::IndexBuffer> indexBufferCube;

		m_VertexArrayCube = Ayo::VertexArray::Create();

		/* Vertices */
        float vertices[] = {
            // Vertices           // Tex coords     // Normals
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,        0.0f,  0.0f, -1.0f,
             0.5f, -0.5f, -0.5f,  1.0f, 0.0f,        0.0f,  0.0f, -1.0f,
             0.5f,  0.5f, -0.5f,  1.0f, 1.0f,        0.0f,  0.0f, -1.0f,
             0.5f,  0.5f, -0.5f,  1.0f, 1.0f,        0.0f,  0.0f, -1.0f,
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,        0.0f,  0.0f, -1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,        0.0f,  0.0f, -1.0f,

            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,        0.0f,  0.0f, 1.0f,
             0.5f, -0.5f,  0.5f,  1.0f, 0.0f,        0.0f,  0.0f, 1.0f,
             0.5f,  0.5f,  0.5f,  1.0f, 1.0f,        0.0f,  0.0f, 1.0f,
             0.5f,  0.5f,  0.5f,  1.0f, 1.0f,        0.0f,  0.0f, 1.0f,
            -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,        0.0f,  0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,        0.0f,  0.0f, 1.0f,

            -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,       -1.0f,  0.0f,  0.0f,
            -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,       -1.0f,  0.0f,  0.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,       -1.0f,  0.0f,  0.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,       -1.0f,  0.0f,  0.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,       -1.0f,  0.0f,  0.0f,
            -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,       -1.0f,  0.0f,  0.0f,

             0.5f,  0.5f,  0.5f,  1.0f, 0.0f,        1.0f,  0.0f,  0.0f,
             0.5f,  0.5f, -0.5f,  1.0f, 1.0f,        1.0f,  0.0f,  0.0f,
             0.5f, -0.5f, -0.5f,  0.0f, 1.0f,        1.0f,  0.0f,  0.0f,
             0.5f, -0.5f, -0.5f,  0.0f, 1.0f,        1.0f,  0.0f,  0.0f,
             0.5f, -0.5f,  0.5f,  0.0f, 0.0f,        1.0f,  0.0f,  0.0f,
             0.5f,  0.5f,  0.5f,  1.0f, 0.0f,        1.0f,  0.0f,  0.0f,

            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,        0.0f, -1.0f,  0.0f,
             0.5f, -0.5f, -0.5f,  1.0f, 1.0f,        0.0f, -1.0f,  0.0f,
             0.5f, -0.5f,  0.5f,  1.0f, 0.0f,        0.0f, -1.0f,  0.0f,
             0.5f, -0.5f,  0.5f,  1.0f, 0.0f,        0.0f, -1.0f,  0.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,        0.0f, -1.0f,  0.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,        0.0f, -1.0f,  0.0f,

            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,        0.0f,  1.0f,  0.0f,
             0.5f,  0.5f, -0.5f,  1.0f, 1.0f,        0.0f,  1.0f,  0.0f,
             0.5f,  0.5f,  0.5f,  1.0f, 0.0f,        0.0f,  1.0f,  0.0f,
             0.5f,  0.5f,  0.5f,  1.0f, 0.0f,        0.0f,  1.0f,  0.0f,
            -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,        0.0f,  1.0f,  0.0f,
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,        0.0f,  1.0f,  0.0f
        };

		vertexBufferCube = Ayo::VertexBuffer::Create(vertices, sizeof(vertices));

		/* Layout */
		Ayo::BufferLayout layout = {
			{ Ayo::ShaderDataType::Float3, "a_Position"},
            { Ayo::ShaderDataType::Float2, "a_TexCoord"},
            { Ayo::ShaderDataType::Float3, "a_Normal"}
		};

		vertexBufferCube->SetLayout(layout);

		/* Indices */
		unsigned int indices[] = {  
                                    0,  1,  2,  3,  4,  5,
                                    6,  7,  8,  9,  10, 11,
                                    12, 13, 14, 15, 16, 17, 
                                    18, 19, 20, 21, 22, 23, 
                                    24, 25, 26, 27, 28, 29, 
                                    30, 31, 32, 33, 34, 35 
                                 };
		indexBufferCube = Ayo::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));

		/* Final Binding to VertexArray */
		m_VertexArrayCube->AddVertexBuffer(vertexBufferCube);
		m_VertexArrayCube->SetIndexBuffer(indexBufferCube);

		/* Shaders */
		// todo: remember to add in model matrix
		std::string vertexSourcePath = AppSettings::DEBUG_ROOT_PATH + "/posTexphong.vs";
		std::string fragmentSourcePath = AppSettings::DEBUG_ROOT_PATH + "/2texturesphong.fs";

		// shader
		m_Shader = Ayo::Shader::CreateFromPath(vertexSourcePath, fragmentSourcePath);

        // Textures
        std::string texturePath = AppSettings::DEBUG_ROOT_PATH + "/container.jpg";
        std::string texture1Path = AppSettings::DEBUG_ROOT_PATH + "/awesomeface.png";

        m_Texture = Ayo::Texture::Create(texturePath);
        m_Texture1 = Ayo::Texture::Create(texture1Path);

		m_Camera->SetLocalLocation(Ayo::Vector3(0.0f, 0.0f, 3.0f));

        // Setup DirLight

        m_DirLight = std::make_shared<Ayo::DirectionalLightSource>(glm::vec3{1.0f, 1.0f, 1.0f}, 1.0f);

        m_DirLight->SetLocalLocation({ 0.0f, 0.3f, 1.0f });
        m_DirLight->SetLocalRotation({ 0.0f, 0.0f, 0.0f });
        m_DirLight->SetLocalScale({ 0.2f, 0.2f, 0.2f });

        vertexSourcePath = AppSettings::DEBUG_ROOT_PATH + "/lightPosOnly.vs";
        fragmentSourcePath = AppSettings::DEBUG_ROOT_PATH + "/lightColor.fs";

        m_DirLightShader = Ayo::Shader::CreateFromPath(vertexSourcePath, fragmentSourcePath);

        //m_Camera->SetLocalRotation({0.0f, 45.0f, 0.0f});
	}

	void OnUpdate() override
	{
        Ayo::Time::Update();
        //AYO_INFO("Time::GetDeltaTime(): {0}", Ayo::Time::GetDeltaTime());
        //AYO_INFO("FPS: {0}", 1.0f/Ayo::Time::GetDeltaTime());
		//AYO_INFO("ExampleLayer::Update");

        /* ----------- Camera Controls ----------- */

        // horizontal movement of camera
		if (Ayo::Input::IsKeyPressed(AYO_KEY_LEFT)) {
            m_Camera->AddLocalOffset(Ayo::Vector3(-speed, 0.0f, 0.0f));
		}
		else if (Ayo::Input::IsKeyPressed(AYO_KEY_RIGHT)) {
            m_Camera->AddLocalOffset(Ayo::Vector3(speed, 0.0f, 0.0f));
        }

        // in/out movement of camera
        if (Ayo::Input::IsKeyPressed(AYO_KEY_UP)) {
            m_Camera->AddLocalOffset(Ayo::Vector3(0.0f, 0.0f, -speed));
        }
        else if (Ayo::Input::IsKeyPressed(AYO_KEY_DOWN)) {
            m_Camera->AddLocalOffset(Ayo::Vector3(0.0f, 0.0f, speed));
        }

        // vertical movement of camera
        if (Ayo::Input::IsKeyPressed(AYO_KEY_SPACE)) {
            m_Camera->AddLocalOffset(Ayo::Vector3(0.0f, speed, 0.0f));
        }
        else if (Ayo::Input::IsKeyPressed(AYO_KEY_LEFT_CONTROL)) {
            m_Camera->AddLocalOffset(Ayo::Vector3(0.0f, -speed, 0.0f));
        }

        // yaw modification of camera
        if (Ayo::Input::IsKeyPressed(AYO_KEY_Z)) {
            m_Camera->AddLocalRotation({ 0.0f, rotSpeed, 0.0f });
            AYO_INFO("Camera Rotation // Pitch: {0}, Yaw: {1}, Roll: {2}", m_Camera->GetLocalRotation().Pitch, m_Camera->GetLocalRotation().Yaw, m_Camera->GetLocalRotation().Roll);
        }
        else if (Ayo::Input::IsKeyPressed(AYO_KEY_C)) {
            m_Camera->AddLocalRotation({ 0.0f, -rotSpeed, 0.0f });
            AYO_INFO("Camera Rotation // Pitch: {0}, Yaw: {1}, Roll: {2}", m_Camera->GetLocalRotation().Pitch, m_Camera->GetLocalRotation().Yaw, m_Camera->GetLocalRotation().Roll);
        }

        // pitch modification of camera
        if (Ayo::Input::IsKeyPressed(AYO_KEY_EQUAL)) {
            m_Camera->AddLocalRotation({ rotSpeed, 0.0f, 0.0f });
        }
        else if (Ayo::Input::IsKeyPressed(AYO_KEY_MINUS)) {
            m_Camera->AddLocalRotation({ -rotSpeed, 0.0f, 0.0f });
        }

        /* -------------------------------------------- */


        if (Ayo::Input::IsKeyPressed(AYO_KEY_1)) {
            m_WireframeMode = !m_WireframeMode;
            Ayo::RenderCommand::SetWireframeMode(m_WireframeMode);
        }

        /* ----------- Light source Controls ----------- */

        // Vertical movement of cube
        if (Ayo::Input::IsKeyPressed(AYO_KEY_W)) {
            m_DirLight->AddLocalOffset({ 0.0f, speed, 0.0f });
        }
        else if (Ayo::Input::IsKeyPressed(AYO_KEY_S)) {
            m_DirLight->AddLocalOffset({ 0.0f, -speed, 0.0f });
        }

        // horizontal movement of cube
        if (Ayo::Input::IsKeyPressed(AYO_KEY_A)) {
            m_DirLight->AddLocalOffset({ speed, 0.0f, 0.0f });
        }
        else if (Ayo::Input::IsKeyPressed(AYO_KEY_D)) {
            m_DirLight->AddLocalOffset({ -speed, 0.0f, 0.0f });
        }

        // depth movement of cube
        if (Ayo::Input::IsKeyPressed(AYO_KEY_V)) {
            m_DirLight->AddLocalOffset({ 0.0f, 0.0f, -speed });
        }
        else if (Ayo::Input::IsKeyPressed(AYO_KEY_B)) {
            m_DirLight->AddLocalOffset({ 0.0f, 0.0f, speed });
        }

        // Changing the object's yaw
        if (Ayo::Input::IsKeyPressed(AYO_KEY_Q)) {
            m_DirLight->AddLocalRotation({ 0.0f, rotSpeed, 0.0f });
        }
        else if (Ayo::Input::IsKeyPressed(AYO_KEY_E)) {
            m_DirLight->AddLocalRotation({ 0.0f, -rotSpeed, 0.0f });
        }

        // Changing the object's pitch
        if (Ayo::Input::IsKeyPressed(AYO_KEY_R)) {
            m_DirLight->AddLocalRotation({ rotSpeed, 0.0f, 0.0f });
        }
        else if (Ayo::Input::IsKeyPressed(AYO_KEY_F)) {
            m_DirLight->AddLocalRotation({ -rotSpeed, 0.0f, 0.0f });
        }

        /* -------------------------------------------- */

        /* ----------- Object Controls ----------- */

  //      // Vertical movement of cube
  //      if (Ayo::Input::IsKeyPressed(AYO_KEY_W)) {
  //          modelTransform = glm::translate(modelTransform, glm::vec3(0.0f, speed, 0.0f));
  //      } else if (Ayo::Input::IsKeyPressed(AYO_KEY_S))
  //      {
  //          modelTransform = glm::translate(modelTransform, glm::vec3(0.0f, -speed, 0.0f));
  //      }

  //      // horizontal movement of cube
  //      if (Ayo::Input::IsKeyPressed(AYO_KEY_A)) {
  //          modelTransform = glm::translate(modelTransform, glm::vec3(speed, 0.0f, 0.0f));
  //      }
  //      else if (Ayo::Input::IsKeyPressed(AYO_KEY_D)) {
  //          modelTransform = glm::translate(modelTransform, glm::vec3(-speed, 0.0f, 0.0f));
  //      }

  //      // Changing the object's yaw
		//if (Ayo::Input::IsKeyPressed(AYO_KEY_Q)) {
		//	//m_Camera->Rotate(rotSpeed, m_Camera->GetForwardVector());
  //          modelTransform = glm::rotate(modelTransform, glm::radians(-rotSpeed), glm::vec3(0.0f, 1.0f, 0.0f));
		//}
		//else if (Ayo::Input::IsKeyPressed(AYO_KEY_E)) {
		//	//m_Camera->Rotate(-rotSpeed, m_Camera->GetForwardVector());
  //          modelTransform = glm::rotate(modelTransform, glm::radians(rotSpeed), glm::vec3(0.0f, 1.0f, 0.0f));
		//}

  //      // Changing the object's pitch
  //      if (Ayo::Input::IsKeyPressed(AYO_KEY_R)) {
  //          //m_Camera->Rotate(rotSpeed, m_Camera->GetForwardVector());
  //          modelTransform = glm::rotate(modelTransform, glm::radians(rotSpeed), glm::vec3(1.0f, 0.0f, 0.0f));
  //      }
  //      else if (Ayo::Input::IsKeyPressed(AYO_KEY_F)) {
  //          //m_Camera->Rotate(-rotSpeed, m_Camera->GetForwardVector());
  //          modelTransform = glm::rotate(modelTransform, glm::radians(-rotSpeed), glm::vec3(1.0f, 0.0f, 0.0f));
  //      }

        /* -------------------------------------------- */

        m_Camera->RecalculateViewProjectionMatrix();

        //Ayo::RenderCommand::SetClearColor({ 0.95f, 0.0625f, 0.93f, 1.0f });
        Ayo::RenderCommand::SetClearColor({ 0.0f, 0.0f, 0.0f, 1.0f });
		Ayo::RenderCommand::Clear();

		Ayo::Renderer::BeginScene();

        glm::mat4 normalMatrix;

		m_Shader->Bind();
        m_Shader->UpdateFloat3Constant("u_ViewPosition", m_Camera->GetLocalLocation().Get());

        m_Shader->UpdateMat4Constant("u_ViewProjectionMatrix", m_Camera->GetViewProjectionMatrix());
        m_Shader->UpdateMat4Constant("u_ModelMatrix", modelTransform);

        normalMatrix = glm::transpose(glm::inverse(modelTransform));
        m_Shader->UpdateMat4Constant("u_NormalMatrix", normalMatrix);

        m_Shader->UpdateFloat3Constant("u_PointLightPosition", m_DirLight->GetLocalLocation().Get());
        m_Shader->UpdateFloat3Constant("u_SpecColor", m_SpecularColor);

        m_DirLight->SetupShader(m_Shader);

        // texture
        m_Shader->UpdateIntConstant("u_Texture", 0);
        m_Texture->Bind(0);
        m_Shader->UpdateIntConstant("u_Texture1", 1);
        m_Texture1->Bind(1);
		m_VertexArrayCube->Bind();
		Ayo::Renderer::Submit(m_VertexArrayCube);

        m_DirLightShader->Bind();

        m_DirLightShader->UpdateMat4Constant("u_ViewProjectionMatrix", m_Camera->GetViewProjectionMatrix() );
        m_DirLightShader->UpdateMat4Constant("u_ModelMatrix", m_DirLight->GetRelativeTransform());
        m_DirLight->SetupShader(m_DirLightShader);
        m_DirLight->Draw();

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
    
    glm::mat4 modelTransform;

    std::shared_ptr<Ayo::Shader> m_Shader;

    std::shared_ptr<Ayo::Shader> m_DirLightShader;

    std::shared_ptr<Ayo::Texture> m_Texture;
    std::shared_ptr<Ayo::Texture> m_Texture1;

	std::shared_ptr<Ayo::Camera> m_Camera;

    std::shared_ptr<Ayo::DirectionalLightSource> m_DirLight;

    glm::vec3 m_SpecularColor = { 0.5f, 0.5f, 0.5f };

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