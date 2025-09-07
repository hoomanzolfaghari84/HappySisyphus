#include "hspch.h"

#include "OrthographicCameraController.h"

#include "Sisyphus/Core/Input.h"
#include "Sisyphus/Core/KeyCodes.h"

namespace Sisyphus {

	OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation) :
		m_AspectRatio(aspectRatio), m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio*m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel), m_Rotation(rotation) {

	}
	
	void OrthographicCameraController::OnUpdate(Timestep ts) {

		if (Input::IsKeyPressed(Key::A)) {
			m_CameraPosition.x -= m_CameraTranslationSpeed * ts;
		}

		else if (Input::IsKeyPressed(Key::D)) {
			m_CameraPosition.x += m_CameraTranslationSpeed * ts;
		}

		if (Input::IsKeyPressed(Key::W)) {
			m_CameraPosition.y += m_CameraTranslationSpeed * ts;
		}

		else if (Input::IsKeyPressed(Key::S)) {
			m_CameraPosition.y -= m_CameraTranslationSpeed * ts;
		}

		m_Camera.SetPosition(m_CameraPosition);

		if(m_Rotation) {

			if (Input::IsKeyPressed(Key::Q)) {
				m_CameraRotation += m_CameraRotationSpeed * ts;
			}
			else if (Input::IsKeyPressed(Key::E))
			{
				m_CameraRotation -= m_CameraRotationSpeed * ts;

			}

			m_Camera.SetRotation(m_CameraRotation);

			m_CameraTranslationSpeed = m_ZoomLevel;
		}

	}

	void OrthographicCameraController::OnEvent(Event& e) {
		EventDispatcher dispatcher(e);

		dispatcher.Dispatch<MouseScrolledEvent>(SP_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
		dispatcher.Dispatch<WindowResizeEvent>(SP_BIND_EVENT_FN(OrthographicCameraController::OnWindowResized));
	}

	bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& e)
	{

		m_ZoomLevel -= e.GetYOffset() * 0.25f;
		m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		return false;
	}

	bool OrthographicCameraController::OnWindowResized(WindowResizeEvent& e)
	{
		m_AspectRatio = (float) e.GetWidth() / (float) e.GetHeight();
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		return false;
	}

}