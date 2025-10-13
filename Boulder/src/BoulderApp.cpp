#include <iostream>

#include <Sisyphus.h>
// -------- Entry Point --------------
#include "Sisyphus/Core/EntryPoint.h"
// -----------------------------------

#include "EditorLayer.h"

class BoulderApp : public Sisyphus::Application
{

public:
	BoulderApp(const Sisyphus::ApplicationSpecification& specification)
		: Sisyphus::Application(specification)
	{
		PushLayer(new Sisyphus::EditorLayer());
	}

	~BoulderApp()
	{

	}
};


Sisyphus::Application* Sisyphus::CreateApplication(Sisyphus::ApplicationCommandLineArgs args)
{
	ApplicationSpecification spec;
	spec.Name = "Boulder";
	spec.WorkingDirectory = "";//"../Boulder";
	spec.CommandLineArgs = args;

	return new BoulderApp(spec);
}