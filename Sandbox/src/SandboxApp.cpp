#include <Ayo.h>

class ExampleLayer : public Ayo::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
	}

	void OnUpdate() override
	{
		AYO_INFO("ExampleLayer::Update");
	}

	void OnEvent(Ayo::Event& e) override
	{
		AYO_TRACE("{0}", e);
	}
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