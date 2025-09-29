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

	// Cube vertices: positions + normals
	float cubeVertices[] = {
		// positions            // normals
		// Back face (-Z)
		-0.5f, -0.5f, -0.5f,   0.0f,  0.0f, -1.0f,
		 0.5f, -0.5f, -0.5f,   0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,   0.0f,  0.0f, -1.0f,
		-0.5f,  0.5f, -0.5f,   0.0f,  0.0f, -1.0f,

		// Front face (+Z)
		-0.5f, -0.5f,  0.5f,   0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,   0.0f,  0.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,   0.0f,  0.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,   0.0f,  0.0f,  1.0f,

		// Left face (-X)
		-0.5f, -0.5f, -0.5f,  -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  -1.0f,  0.0f,  0.0f,

		// Right face (+X)
		 0.5f, -0.5f, -0.5f,   1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,   1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,   1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,   1.0f,  0.0f,  0.0f,

		 // Bottom face (-Y)
		 -0.5f, -0.5f, -0.5f,   0.0f, -1.0f,  0.0f,
		  0.5f, -0.5f, -0.5f,   0.0f, -1.0f,  0.0f,
		  0.5f, -0.5f,  0.5f,   0.0f, -1.0f,  0.0f,
		 -0.5f, -0.5f,  0.5f,   0.0f, -1.0f,  0.0f,

		 // Top face (+Y)
		 -0.5f,  0.5f, -0.5f,   0.0f,  1.0f,  0.0f,
		  0.5f,  0.5f, -0.5f,   0.0f,  1.0f,  0.0f,
		  0.5f,  0.5f,  0.5f,   0.0f,  1.0f,  0.0f,
		 -0.5f,  0.5f,  0.5f,   0.0f,  1.0f,  0.0f,
	};

	uint32_t cubeIndices[] = {
		0, 1, 2, 2, 3, 0,        // back
		4, 5, 6, 6, 7, 4,        // front
		8, 9,10,10,11, 8,        // left
	   12,13,14,14,15,12,        // right
	   16,17,18,18,19,16,        // bottom
	   20,21,22,22,23,20         // top
	};

	
	m_CubeMesh = Sisyphus::CreateRef<Sisyphus::Mesh>(
					cubeVertices,
					sizeof(cubeVertices),
					cubeIndices,
					sizeof(cubeIndices) / sizeof(uint32_t)
	);


	m_LightMesh = Sisyphus::CreateRef<Sisyphus::Mesh>(
		cubeVertices,
		sizeof(cubeVertices),
		cubeIndices,
		sizeof(cubeIndices) / sizeof(uint32_t)
	);


}

void Sandbox3D::OnDetach()
{
}

void Sandbox3D::OnUpdate(Sisyphus::Timestep ts)
{
	// Input
	if (Sisyphus::Input::IsMouseButtonPressed(Sisyphus::Mouse::ButtonRight)) {
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
		glm::vec2 mousePos = Sisyphus::Input::GetMousePosition();
		glm::vec2 delta = mousePos - lastMousePos;
		lastMousePos = mousePos;

		float sensitivity = 0.1f;
		m_Camera.ProcessRotation(delta.x * sensitivity, -delta.y * sensitivity);
	}


	// Update

	
	// Render

	Sisyphus::RenderCommand::SetClearColor({ 0.1, 0.1, 0.1, 1.0 });
	Sisyphus::RenderCommand::Clear();


	glm::mat4 model = glm::mat4(1.0f); // Cube at origin
	glm::vec3 lightPosition{ 1.2f, 1.0f, 2.0f };

	Sisyphus::Renderer3D::BeginScene(m_Camera);

	Sisyphus::Renderer3D::DrawMesh(m_CubeMesh, model, m_CubeColor, lightPosition);

	
	model = glm::translate(model, lightPosition);
	model = glm::scale(model, glm::vec3(0.2f));
	Sisyphus::Renderer3D::DrawLight(m_LightMesh, model);

	Sisyphus::Renderer3D::EndScene();
}

void Sandbox3D::OnImGuiRender()
{
	ImGui::Begin("Settings");

	ImGui::ColorEdit4("Cube Base Color", glm::value_ptr(m_CubeColor));

	ImGui::End();
}

void Sandbox3D::OnEvent(Sisyphus::Event& e)
{
	Sisyphus::EventDispatcher dispatcher(e);

	dispatcher.Dispatch<Sisyphus::MouseButtonPressedEvent>([this](Sisyphus::MouseButtonPressedEvent& e)
	{
		if (e.GetMouseButton() == Sisyphus::Mouse::ButtonRight) {
			lastMousePos = Sisyphus::Input::GetMousePosition();
		}
			
		return false;
	});

	dispatcher.Dispatch<Sisyphus::KeyPressedEvent>([this](Sisyphus::KeyPressedEvent& e)
	{
		if (e.GetKeyCode() == Sisyphus::Key::F) {
			m_Camera = Sisyphus::FlyCamera(45.0f,
				(float)Sisyphus::Application::Get().GetWindow().GetWidth() / (float)Sisyphus::Application::Get().GetWindow().GetHeight(),
				0.1f, 100.0f);
		}

		return false;
	});

	dispatcher.Dispatch<Sisyphus::MouseScrolledEvent>([this](Sisyphus::MouseScrolledEvent& e)
	{
		m_Camera.Zoom(e.GetYOffset() * 1.0f); // adjust zoom speed
		return false;
	});
}
