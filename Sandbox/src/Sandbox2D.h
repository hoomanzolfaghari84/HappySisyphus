#pragma once

#include <Sisyphus.h>

class Sandbox2D : public Sisyphus::Layer
{
public:

	Sandbox2D();
	~Sandbox2D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(Sisyphus::Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(Sisyphus::Event& e) override;

	
private:
	Sisyphus::OrthographicCameraController m_CameraController;

	// Temp
	Sisyphus::Ref<Sisyphus::Shader> m_FlatColorShader;
	Sisyphus::Ref<Sisyphus::VertexArray> m_SquareVA;

	Sisyphus::Ref<Sisyphus::Texture2D> m_Texture;


	glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f , 1.f};



};

