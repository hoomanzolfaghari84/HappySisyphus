#pragma once

#include "Sisyphus/Renderer/OrthographicCamera.h"
#include "Sisyphus/Core/Timestep.h"
#include "Sisyphus/Events/ApplicationEvent.h"
#include "Sisyphus/Events/MouseEvent.h"

namespace Sisyphus {

	class OrthographicCameraController
	{
	public:
		OrthographicCameraController(float aspectRatio, bool rotation = false);
		void SetProjection(float left, float right, float bottom, float top);

		void OnUpdate(Timestep ts);
		void OnEvent(Event& e);

		OrthographicCamera& GetCamera() {
			return m_Camera;
		}

		const OrthographicCamera& GetCamera() const {
			return m_Camera;
		}

		void SetZoomLevel(float level) {
			m_ZoomLevel = level;
		}

		float GetZoomLevel() {
			return m_ZoomLevel;
		}

	private:
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResized(WindowResizeEvent& e);

	private:
		float m_AspectRatio;
		float m_ZoomLevel = 1.0f;
		OrthographicCamera m_Camera;

		bool m_Rotation;

		glm::vec3 m_CameraPosition = { 0.f, 0.f, 0.f };
		float m_CameraRotation = 0.f;
		float m_CameraTranslationSpeed = 5.f, m_CameraRotationSpeed = 180.f;

	};

}