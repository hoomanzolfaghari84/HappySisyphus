#include <iostream>

#include <Sisyphus.h>
// -------- Entry Point --------------
#include "Sisyphus/Core/EntryPoint.h"
// -----------------------------------

#include "Sandbox2D.h"
#include "Sandbox3D.h"

#include "imgui-forked/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class SandboxApp : public Sisyphus::Application
{

public:
	SandboxApp(const Sisyphus::ApplicationSpecification& specification)
		: Sisyphus::Application(specification)
	{
		//PushLayer(new Sandbox2D());
		PushLayer(new Sandbox3D());
		SIPH_TRACE("Sandbox App Initialized");
	}

	~SandboxApp()
	{

	}
};


Sisyphus::Application* Sisyphus::CreateApplication(Sisyphus::ApplicationCommandLineArgs args)
{
	ApplicationSpecification spec;
	spec.Name = "Sandbox";
	spec.WorkingDirectory = "";//"../Boulder";
	spec.CommandLineArgs = args;

	return new SandboxApp(spec);
}