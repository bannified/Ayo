#pragma once

#ifdef AYO_PLATFORM_WINDOWS

// function defined externally.
extern Ayo::Application* Ayo::CreateApplication();

int main(int argc, char** argv)
{
	Ayo::Log::Init();
	AYO_CORE_WARN("Initialized Log!");

	int a = 5;
	AYO_INFO("Hello! Var={0}", a);

	auto app = Ayo::CreateApplication();
	app->Run();
	delete app;
}

#else

#endif