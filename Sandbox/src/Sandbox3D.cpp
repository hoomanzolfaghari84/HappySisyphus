#include "Sandbox3D.h"

#include <imgui/imgui.h>


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Sandbox3D::Sandbox3D() : Layer("Sandbox2D")
{
}

void Sandbox3D::OnAttach()
{
	cubeVAO = Sisyphus::VertexArray::Create();

	// Cube vertices: positions + normals
	float cubeVertices[] = {
		// positions          // normals
		-0.5f, -0.5f, -0.5f,   0.0f,  0.0f, -1.0f, // 0
		 0.5f, -0.5f, -0.5f,   0.0f,  0.0f, -1.0f, // 1
		 0.5f,  0.5f, -0.5f,   0.0f,  0.0f, -1.0f, // 2
		-0.5f,  0.5f, -0.5f,   0.0f,  0.0f, -1.0f, // 3

		-0.5f, -0.5f,  0.5f,   0.0f,  0.0f,  1.0f, // 4
		 0.5f, -0.5f,  0.5f,   0.0f,  0.0f,  1.0f, // 5
		 0.5f,  0.5f,  0.5f,   0.0f,  0.0f,  1.0f, // 6
		-0.5f,  0.5f,  0.5f,   0.0f,  0.0f,  1.0f, // 7
	};

	uint32_t cubeIndices[] = {
		// back face
		0, 1, 2, 2, 3, 0,
		// front face
		4, 5, 6, 6, 7, 4,
		// left face
		0, 3, 7, 7, 4, 0,
		// right face
		1, 5, 6, 6, 2, 1,
		// bottom face
		0, 1, 5, 5, 4, 0,
		// top face
		3, 2, 6, 6, 7, 3
	};

	cubeVBO = Sisyphus::VertexBuffer::Create(cubeVertices, sizeof(cubeVertices));
	cubeVBO->SetLayout({
		{ Sisyphus::ShaderDataType::Float3, "aPos" },
		{ Sisyphus::ShaderDataType::Float3, "aNormal" }
		});

	cubeVAO->AddVertexBuffer(cubeVBO);

	auto cubeIBO = Sisyphus::IndexBuffer::Create(cubeIndices, sizeof(cubeIndices) / sizeof(uint32_t));
	cubeVAO->SetIndexBuffer(cubeIBO);

	cubeShader = Sisyphus::Shader::Create("assets/shaders/Basic3D.glsl");
	/*m_Camera = Sisyphus::FlyCamera(
			glm::radians(45.0f),
			(float)Sisyphus::Application::Get().GetWindow().GetWidth() / (float)Sisyphus::Application::Get().GetWindow().GetHeight(),
			0.1f,
			100.0f);*/

	//m_Camera.SetPosition(glm::vec3{ 2.0f, 2.0f, 2.0f });
	
}

void Sandbox3D::OnDetach()
{
}

void Sandbox3D::OnUpdate(Sisyphus::Timestep ts)
{
	// Input

	// --- Keyboard Input ---
	glm::vec3 direction(0.0f);
	if (Sisyphus::Input::IsKeyPressed(Sisyphus::Key::W))
		direction += m_Camera.GetFront();
	if (Sisyphus::Input::IsKeyPressed(Sisyphus::Key::S))
		direction -= m_Camera.GetFront();
	if (Sisyphus::Input::IsKeyPressed(Sisyphus::Key::A))
		direction -= glm::normalize(glm::cross(m_Camera.GetFront(), glm::vec3(0.0f, 1.0f, 0.0f)));
	if (Sisyphus::Input::IsKeyPressed(Sisyphus::Key::D))
		direction += glm::normalize(glm::cross(m_Camera.GetFront(), glm::vec3(0.0f, 1.0f, 0.0f)));
	if (Sisyphus::Input::IsKeyPressed(Sisyphus::Key::Space))
		direction += glm::vec3(0.0f, 1.0f, 0.0f);
	if (Sisyphus::Input::IsKeyPressed(Sisyphus::Key::LeftControl))
		direction -= glm::vec3(0.0f, 1.0f, 0.0f);

	if (glm::length(direction) > 0.0f)
		m_Camera.ProcessMovement(glm::normalize(direction), ts);

	// --- Mouse Input ---
	static glm::vec2 lastMousePos = Sisyphus::Input::GetMousePosition();
	glm::vec2 mousePos = Sisyphus::Input::GetMousePosition();
	glm::vec2 delta = mousePos - lastMousePos;
	lastMousePos = mousePos;

	float sensitivity = 0.1f;
	m_Camera.ProcessRotation(delta.x * sensitivity, -delta.y * sensitivity);


	// Update

	
	// Render

	Sisyphus::RenderCommand::SetClearColor({ 0.1, 0.1, 0.1, 1.0 });
	Sisyphus::RenderCommand::Clear();

	// Camera/View/Projection

	glm::mat4 projection = m_Camera.GetProjection();
	/*glm::mat4 projection = glm::perspective(glm::radians(45.0f),
		(float)Sisyphus::Application::Get().GetWindow().GetWidth() / (float)Sisyphus::Application::Get().GetWindow().GetHeight(),
		0.1f, 100.0f);*/
	glm::mat4 view = m_Camera.GetViewMatrix();
	//glm::mat4 view = glm::lookAt(glm::vec3(2.0f, 2.0f, 2.0f), // Camera position
	//	glm::vec3(0.0f, 0.0f, 0.0f), // Look at origin
	//	glm::vec3(0.0f, 1.0f, 0.0f)); // Up vector

	glm::mat4 model = glm::mat4(1.0f); // Cube at origin

	cubeShader->Bind();
	cubeShader->SetMat4("u_Model", model);
	cubeShader->SetMat4("u_View", view);
	cubeShader->SetMat4("u_Projection", projection);

	// Light & color
	cubeShader->SetFloat4("u_ObjectColor", m_CubeColor);

	cubeVAO->Bind();
	Sisyphus::RenderCommand::DrawIndexed(cubeVAO);
}

void Sandbox3D::OnImGuiRender()
{
	ImGui::Begin("Settings");

	ImGui::ColorEdit4("Squares Color", glm::value_ptr(m_CubeColor));

	ImGui::End();
}


//bool OnWindowResized(Sisyphus::WindowResizeEvent& e)
//{
//	m_AspectRatio = (float)e.GetWidth() / (float)e.GetHeight();
//	m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
//	return false;
//}

void Sandbox3D::OnEvent(Sisyphus::Event& e)
{
	Sisyphus::EventDispatcher dispatcher(e);

	dispatcher.Dispatch<Sisyphus::MouseScrolledEvent>([this](Sisyphus::MouseScrolledEvent& e)
	{
		m_Camera.Zoom(e.GetYOffset() * 1.0f); // adjust zoom speed
		return false;
	});
	//dispatcher.Dispatch<Sisyphus::WindowResizeEvent>(SP_BIND_EVENT_FN(OrthographicCameraController::OnWindowResized));
}
