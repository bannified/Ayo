#pragma once

#ifdef AYO_PLATFORM_WINDOWS

// function defined externally.
extern Ayo::Application* Ayo::CreateApplication();

int main(int argc, char** argv)
{
	auto app = Ayo::CreateApplication();
	app->Run();
	delete app;
}

#else

#endif