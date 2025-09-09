#include "Sandbox2D.h"

#include <imgui/imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Sandbox2D::Sandbox2D() : Layer("Sandbox2D"), m_CameraController(1280.f / 720.f, true)
{
}

void Sandbox2D::OnAttach()
{


	//m_SquareVA = Sisyphus::VertexArray::Create();


	/*float squareVertices[3 * 4] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.5f,  0.5f, 0.0f,
		-0.5f,  0.5f, 0.0f
	};

	Sisyphus::Ref<Sisyphus::VertexBuffer> squareVB = Sisyphus::VertexBuffer::Create(squareVertices, sizeof(squareVertices));
	squareVB->SetLayout({
			{ Sisyphus::ShaderDataType::Float3, "a_Position" },
		});
	m_SquareVA->AddVertexBuffer(squareVB);

	uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
	Sisyphus::Ref<Sisyphus::IndexBuffer> squareIB;
	squareIB = Sisyphus::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));
	m_SquareVA->SetIndexBuffer(squareIB);

	

	m_FlatColorShader = Sisyphus::Shader::Create("assets/shaders/FlatColor.glsl");*/



}

void Sandbox2D::OnDetach()
{
}

void Sandbox2D::OnUpdate(Sisyphus::Timestep ts)
{
	// Update

	m_CameraController.OnUpdate(ts);

	// Render

	Sisyphus::RenderCommand::SetClearColor({ 0.1, 0.1, 0.1, 1.0 });
	Sisyphus::RenderCommand::Clear();


	Sisyphus::Renderer2D::BeginScene(m_CameraController.GetCamera());

	/*m_FlatColorShader->Bind();
	m_FlatColorShader->SetFloat4("u_Color", m_SquareColor);

	Sisyphus::Renderer::Submit(m_FlatColorShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5)));*/

	Sisyphus::Renderer2D::DrawQuad(glm::scale(glm::mat4(1.0f), glm::vec3(1.5)), m_SquareColor);

	Sisyphus::Renderer2D::EndScene();
}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Settings");

	ImGui::ColorEdit4("Squares Color", glm::value_ptr(m_SquareColor));

	ImGui::End();
}

void Sandbox2D::OnEvent(Sisyphus::Event& e)
{
	m_CameraController.OnEvent(e);

}
