#pragma once

#include <Sisyphus.h>

class Sandbox3D : public Sisyphus::Layer
{
public:

	Sandbox3D();
	~Sandbox3D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(Sisyphus::Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(Sisyphus::Event& e) override;


private:
	Sisyphus::PerspectiveCamera m_Camera{ 45.0f, 1280.0f / 720.0f, 0.1f, 100.0f };
	Sisyphus::Ref<Sisyphus::Mesh> m_CubeMesh;
};

