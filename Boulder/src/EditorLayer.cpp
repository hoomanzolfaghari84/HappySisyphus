#include "EditorLayer.h"

#include <imgui-forked/imgui.h>


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Sisyphus {


	EditorLayer::EditorLayer() : Layer("EditorLayer")
	{
	}

	void EditorLayer::OnAttach()
	{
		// Cube vertices: positions + normals + texture coords
		float cubeVertices[] = {
			// Back face (-Z)
			-0.5f, -0.5f, -0.5f,   0.0f,  0.0f, -1.0f,   0.0f, 0.0f,
			 0.5f, -0.5f, -0.5f,   0.0f,  0.0f, -1.0f,   1.0f, 0.0f,
			 0.5f,  0.5f, -0.5f,   0.0f,  0.0f, -1.0f,   1.0f, 1.0f,
			-0.5f,  0.5f, -0.5f,   0.0f,  0.0f, -1.0f,   0.0f, 1.0f,

			// Front face (+Z)
			-0.5f, -0.5f,  0.5f,   0.0f,  0.0f,  1.0f,   0.0f, 0.0f,
			 0.5f, -0.5f,  0.5f,   0.0f,  0.0f,  1.0f,   1.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,   0.0f,  0.0f,  1.0f,   1.0f, 1.0f,
			-0.5f,  0.5f,  0.5f,   0.0f,  0.0f,  1.0f,   0.0f, 1.0f,

			// Left face (-X)
			-0.5f, -0.5f, -0.5f,  -1.0f,  0.0f,  0.0f,   0.0f, 0.0f,
			-0.5f,  0.5f, -0.5f,  -1.0f,  0.0f,  0.0f,   1.0f, 0.0f,
			-0.5f,  0.5f,  0.5f,  -1.0f,  0.0f,  0.0f,   1.0f, 1.0f,
			-0.5f, -0.5f,  0.5f,  -1.0f,  0.0f,  0.0f,   0.0f, 1.0f,

			// Right face (+X)
			 0.5f, -0.5f, -0.5f,   1.0f,  0.0f,  0.0f,   0.0f, 0.0f,
			 0.5f,  0.5f, -0.5f,   1.0f,  0.0f,  0.0f,   1.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,   1.0f,  0.0f,  0.0f,   1.0f, 1.0f,
			 0.5f, -0.5f,  0.5f,   1.0f,  0.0f,  0.0f,   0.0f, 1.0f,

			 // Bottom face (-Y)
			 -0.5f, -0.5f, -0.5f,   0.0f, -1.0f,  0.0f,   0.0f, 1.0f,
			  0.5f, -0.5f, -0.5f,   0.0f, -1.0f,  0.0f,   1.0f, 1.0f,
			  0.5f, -0.5f,  0.5f,   0.0f, -1.0f,  0.0f,   1.0f, 0.0f,
			 -0.5f, -0.5f,  0.5f,   0.0f, -1.0f,  0.0f,   0.0f, 0.0f,

			 // Top face (+Y)
			 -0.5f,  0.5f, -0.5f,   0.0f,  1.0f,  0.0f,   0.0f, 1.0f,
			  0.5f,  0.5f, -0.5f,   0.0f,  1.0f,  0.0f,   1.0f, 1.0f,
			  0.5f,  0.5f,  0.5f,   0.0f,  1.0f,  0.0f,   1.0f, 0.0f,
			 -0.5f,  0.5f,  0.5f,   0.0f,  1.0f,  0.0f,   0.0f, 0.0f
		};


		// Indices for each face (two triangles per face)
		uint32_t cubeIndices[] = {
			 0,  1,  2,   2,  3,  0,   // back
			 4,  5,  6,   6,  7,  4,   // front
			 8,  9, 10,  10, 11,  8,   // left
			12, 13, 14,  14, 15, 12,   // right
			16, 17, 18,  18, 19, 16,   // bottom
			20, 21, 22,  22, 23, 20    // top
		};

		auto diffuseTex = Sisyphus::Renderer3D::GetTextureLibrary()->Load("assets/textures/container2.png");
		auto specularTex = Sisyphus::Renderer3D::GetTextureLibrary()->Load("assets/textures/container2_specular.png");

		auto material = Sisyphus::CreateRef<Sisyphus::Material>();
		material->SetTexture(Sisyphus::TextureType::Diffuse, diffuseTex);
		material->SetTexture(Sisyphus::TextureType::Specular, specularTex);
		material->SetShininess(64.0f);

		//loaded_mesh->SetMaterial(material);

		m_CubeMesh = Sisyphus::CreateRef<Sisyphus::Mesh>(
			cubeVertices,
			sizeof(cubeVertices),
			cubeIndices,
			sizeof(cubeIndices) / sizeof(uint32_t)
		);
		m_CubeMesh->SetMaterial(material);


		m_LightMesh = Sisyphus::CreateRef<Sisyphus::Mesh>(
			cubeVertices,
			sizeof(cubeVertices),
			cubeIndices,
			sizeof(cubeIndices) / sizeof(uint32_t)
		);


		m_CubeMesh->PrintInfo();

		Sisyphus::FramebufferSpecification fbSpec;
		fbSpec.Width = 1290;
		fbSpec.Height = 720;
		fbSpec.Attachments = {
		{
			{ Sisyphus::FramebufferTextureFormat::RGBA8 },
			{ Sisyphus::FramebufferTextureFormat::RED_INTEGER },
			{ Sisyphus::FramebufferTextureFormat::Depth }
		}
		};

		m_FrameBuffer = Sisyphus::Framebuffer::Create(fbSpec);

	}

	void EditorLayer::OnDetach()
	{
	}

	void EditorLayer::OnUpdate(Sisyphus::Timestep ts)
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
		{
			m_FrameBuffer->Bind();
			Sisyphus::RenderCommand::SetClearColor({ 0.1, 0.1, 0.1, 1.0 });
			Sisyphus::RenderCommand::Clear();
		}


		glm::mat4 model = glm::mat4(1.0f); // Cube at origin
		model = glm::translate(model, m_CubePosition);
		glm::vec3 lightPosition{ 0.5f, 0.5f, 1.2f };

		Sisyphus::Renderer3D::BeginScene(m_Camera);

		m_CubeMesh->GetMaterial()->SetFlatColor(m_CubeColor);
		Sisyphus::Renderer3D::DrawMesh(m_CubeMesh, model, lightPosition);


		/*for (auto mesh : m_Model->GetMeshes())
			Sisyphus::Renderer3D::DrawMesh(mesh, model, lightPosition);*/

		model = glm::mat4(1.0f);
		model = glm::translate(model, lightPosition);
		model = glm::scale(model, glm::vec3(0.2f));
		Sisyphus::Renderer3D::DrawLight(m_LightMesh, model);

		Sisyphus::Renderer3D::EndScene();
		m_FrameBuffer->Unbind();
	}



	void EditorLayer::OnImGuiRender()
	{
		// READ THIS !!!
			// TL;DR; this demo is more complicated than what most users you would normally use.
			// If we remove all options we are showcasing, this demo would become:
			//     void ShowExampleAppDockSpace()
			//     {
			//         ImGui::DockSpaceOverViewport(0, ImGui::GetMainViewport());
			//     }
			// In most cases you should be able to just call DockSpaceOverViewport() and ignore all the code below!
			// In this specific demo, we are not using DockSpaceOverViewport() because:
			// - (1) we allow the host window to be floating/moveable instead of filling the viewport (when opt_fullscreen == false)
			// - (2) we allow the host window to have padding (when opt_padding == true)
			// - (3) we expose many flags and need a way to have them visible.
			// - (4) we have a local menu bar in the host window (vs. you could use BeginMainMenuBar() + DockSpaceOverViewport()
			//      in your code, but we don't here because we allow the window to be floating)

		static bool opt_fullscreen = true;
		static bool opt_padding = false;
		static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

		// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
		// because it would be confusing to have two docking targets within each others.
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
		if (opt_fullscreen)
		{
			const ImGuiViewport* viewport = ImGui::GetMainViewport();
			ImGui::SetNextWindowPos(viewport->WorkPos);
			ImGui::SetNextWindowSize(viewport->WorkSize);
			ImGui::SetNextWindowViewport(viewport->ID);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
			window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
			window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
		}
		else
		{
			dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
		}

		// When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
		// and handle the pass-thru hole, so we ask Begin() to not render a background.
		if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
			window_flags |= ImGuiWindowFlags_NoBackground;

		// Important: note that we proceed even if Begin() returns false (aka window is collapsed).
		// This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
		// all active windows docked into it will lose their parent and become undocked.
		// We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
		// any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
		if (!opt_padding)
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		static bool temp = true;
		static bool* p_open = &temp;
		ImGui::Begin("DockSpace Demo", p_open, window_flags);
		if (!opt_padding)
			ImGui::PopStyleVar();

		if (opt_fullscreen)
			ImGui::PopStyleVar(2);

		// Submit the DockSpace
		ImGuiIO& io = ImGui::GetIO();
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
		}
		else
		{
			//ShowDockingDisabledMessage();
		}

		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("Options"))
			{
				// Disabling fullscreen would allow the window to be moved to the front of other windows,
				// which we can't undo at the moment without finer window depth/z control.
				ImGui::MenuItem("Fullscreen", NULL, &opt_fullscreen);
				ImGui::MenuItem("Padding", NULL, &opt_padding);
				ImGui::Separator();

				if (ImGui::MenuItem("Flag: NoDockingOverCentralNode", "", (dockspace_flags & ImGuiDockNodeFlags_NoDockingOverCentralNode) != 0)) { dockspace_flags ^= ImGuiDockNodeFlags_NoDockingOverCentralNode; }
				if (ImGui::MenuItem("Flag: NoDockingSplit", "", (dockspace_flags & ImGuiDockNodeFlags_NoDockingSplit) != 0)) { dockspace_flags ^= ImGuiDockNodeFlags_NoDockingSplit; }
				if (ImGui::MenuItem("Flag: NoUndocking", "", (dockspace_flags & ImGuiDockNodeFlags_NoUndocking) != 0)) { dockspace_flags ^= ImGuiDockNodeFlags_NoUndocking; }
				if (ImGui::MenuItem("Flag: NoResize", "", (dockspace_flags & ImGuiDockNodeFlags_NoResize) != 0)) { dockspace_flags ^= ImGuiDockNodeFlags_NoResize; }
				if (ImGui::MenuItem("Flag: AutoHideTabBar", "", (dockspace_flags & ImGuiDockNodeFlags_AutoHideTabBar) != 0)) { dockspace_flags ^= ImGuiDockNodeFlags_AutoHideTabBar; }
				if (ImGui::MenuItem("Flag: PassthruCentralNode", "", (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode) != 0, opt_fullscreen)) { dockspace_flags ^= ImGuiDockNodeFlags_PassthruCentralNode; }
				ImGui::Separator();

				if (ImGui::MenuItem("Close", NULL, false, p_open != NULL))
					*p_open = false;
				ImGui::EndMenu();
			}
			Sisyphus::ImGuiLayer::HelpMarker(
				"When docking is enabled, you can ALWAYS dock MOST window into another! Try it now!" "\n"
				"- Drag from window title bar or their tab to dock/undock." "\n"
				"- Drag from window menu button (upper-left button) to undock an entire node (all windows)." "\n"
				"- Hold SHIFT to disable docking (if io.ConfigDockingWithShift == false, default)" "\n"
				"- Hold SHIFT to enable docking (if io.ConfigDockingWithShift == true)" "\n"
				"This demo app has nothing to do with enabling docking!" "\n\n"
				"This demo app only demonstrate the use of ImGui::DockSpace() which allows you to manually create a docking node _within_ another window." "\n\n"
				"Read comments in ShowExampleAppDockSpace() for more details.");

			ImGui::EndMenuBar();
		}


		ImGui::Begin("Settings");

		ImGui::ColorEdit4("Cube Base Color", glm::value_ptr(m_CubeColor));
		ImGui::SliderFloat3("Cube Location", glm::value_ptr(m_CubePosition), -5.0f, 5.0f);

		ImGui::End();

		ImGui::Begin("ViewPort");

		uint32_t colorAttachmentID = m_FrameBuffer->GetColorAttachmentRendererID();
		ImGui::Image((void*)(intptr_t)colorAttachmentID, ImVec2(1280 * 3 / 4, 720 * 3 / 4), ImVec2({0, 1}), ImVec2({1, 0}));

		ImGui::End();

		ImGui::End();


	}

	void EditorLayer::OnEvent(Sisyphus::Event& e)
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




}
