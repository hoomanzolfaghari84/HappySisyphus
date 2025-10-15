#pragma once

#include <Sisyphus.h>

namespace Sisyphus {

	class EditorLayer : public Layer
	{
	public:

		EditorLayer();
		virtual ~EditorLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		void OnUpdate(Sisyphus::Timestep ts) override;
		virtual void OnImGuiRender() override;
		void OnEvent(Sisyphus::Event& e) override;


	private:

		bool OnKeyPressed(KeyPressedEvent& e);
		bool OnMouseButtonPressed(MouseButtonPressedEvent& e);

		void OnOverlayRender();

		/*void NewProject();
		bool OpenProject();
		void OpenProject(const std::filesystem::path& path);
		void SaveProject();

		void NewScene();
		void OpenScene();
		void OpenScene(const std::filesystem::path& path);
		void SaveScene();
		void SaveSceneAs();

		void SerializeScene(Ref<Scene> scene, const std::filesystem::path& path);

		void OnScenePlay();
		void OnSceneSimulate();
		void OnSceneStop();
		void OnScenePause();

		void OnDuplicateEntity();*/

		// UI Panels
		void UI_Toolbar();

	private:

		bool m_PrimaryCamera = true;

		EditorCamera m_EditorCamera;


		Sisyphus::Ref<Sisyphus::Framebuffer> m_FrameBuffer;

		bool m_ViewportFocused = false, m_ViewportHovered = false;
		glm::vec2 m_ViewportSize = { 0.0f, 0.0f };
		glm::vec2 m_ViewportBounds[2];


		glm::vec2 lastMousePos{ 0.f };
		
		Sisyphus::FlyCamera m_Camera{ 45.0f,
			(float)Sisyphus::Application::Get().GetWindow().GetWidth() / (float)Sisyphus::Application::Get().GetWindow().GetHeight(),
			0.1f, 100.0f };


		Sisyphus::Ref<Sisyphus::Mesh> m_CubeMesh;
		glm::vec4 m_CubeColor{ 0.8f, 0.3f, 0.2f, 1.f };
		glm::vec3 m_CubePosition{ 0.0f, 0.0f, 0.0f };

		Sisyphus::Ref<Sisyphus::Mesh> m_LightMesh;

	};


}
