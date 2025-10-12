#pragma once

#include "Sisyphus/Core/Base.h"
#include "Sisyphus/Core/Application.h"
#include <Sisyphus/Debug/Instrumentor.h>

#ifdef SP_PLATFORM_WINDOWS

extern Sisyphus::Application* Sisyphus::CreateApplication(ApplicationCommandLineArgs args);

int main(int argc, char** argv)
{
	Sisyphus::Log::Init();

	HS_PROFILE_BEGIN_SESSION("Startup", "SisyphusProfile-Startup.json");
	auto app = Sisyphus::CreateApplication({ argc, argv });
	HS_PROFILE_END_SESSION();

	HS_PROFILE_BEGIN_SESSION("Runtime", "SisyphusProfile-Runtime.json");
	app->Run();
	HS_PROFILE_END_SESSION();

	HS_PROFILE_BEGIN_SESSION("Shutdown", "SisyphusProfile-Shutdown.json");
	delete app;
	HS_PROFILE_END_SESSION();
}

#endif