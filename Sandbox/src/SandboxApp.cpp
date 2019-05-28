#include <Ayo.h>

class Sandbox : public Ayo::Application
{
	public:
		Sandbox()
		{

		}

		~Sandbox()
		{

		}
};

Ayo::Application* Ayo::CreateApplication()
{
	return new Sandbox();
}