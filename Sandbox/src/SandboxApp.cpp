#include <iostream>
#include <Sisyphus.h>

class ExampleLayer : public Sisyphus::Layer {

public:
	ExampleLayer() : Layer("Example") {

	}

	void OnUpdate(Sisyphus::Timestep ts) override {
		//SIPH_INFO("ExampleLayer::OnUpdate");
	}

	void OnEvent(Sisyphus::Event& event) override {
		//SIPH_TRACE("{0}", event.ToString());
	}
	
};


class SandboxApp : public Sisyphus::Application
{

public:
	SandboxApp(const Sisyphus::ApplicationSpecification& specification)
		: Sisyphus::Application(specification)
	{
		PushLayer(new ExampleLayer());
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
	spec.WorkingDirectory = "../Boulder";
	spec.CommandLineArgs = args;

	return new SandboxApp(spec);
}