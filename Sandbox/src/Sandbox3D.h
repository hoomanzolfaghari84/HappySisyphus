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
	glm::vec2 lastMousePos{ 0.f };
	Sisyphus::FlyCamera m_Camera{ 45.0f,
		(float) Sisyphus::Application::Get().GetWindow().GetWidth()/ (float)Sisyphus::Application::Get().GetWindow().GetHeight(),
		0.1f, 100.0f};


	Sisyphus::Ref<Sisyphus::Mesh> m_CubeMesh;
	glm::vec4 m_CubeColor{ 0.8f, 0.3f, 0.2f, 1.f };
	glm::vec3 m_CubePosition{ 0.0f, 0.0f, 0.0f};

	Sisyphus::Ref<Sisyphus::Mesh> m_LightMesh;

	Sisyphus::Ref<Sisyphus::Model> m_Model;

	Sisyphus::Ref<Sisyphus::Framebuffer> m_FrameBuffer;

};

