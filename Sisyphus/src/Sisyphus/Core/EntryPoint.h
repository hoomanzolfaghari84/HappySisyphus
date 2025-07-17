#pragma once

#include "Sisyphus/Core/Base.h"
#include "Sisyphus/Core/Application.h"

#ifdef SP_PLATFORM_WINDOWS

extern Sisyphus::Application* Sisyphus::CreateApplication(ApplicationCommandLineArgs args);

int main(int argc, char** argv)
{
	Sisyphus::Log::Init();

	//SP_PROFILE_BEGIN_SESSION("Startup", "HazelProfile-Startup.json");
	auto app = Sisyphus::CreateApplication({ argc, argv });
	//SP_PROFILE_END_SESSION();

	//SP_PROFILE_BEGIN_SESSION("Runtime", "HazelProfile-Runtime.json");
	app->Run();
	//SP_PROFILE_END_SESSION();

	//SP_PROFILE_BEGIN_SESSION("Shutdown", "HazelProfile-Shutdown.json");
	delete app;
	//SP_PROFILE_END_SESSION();
}

#endif