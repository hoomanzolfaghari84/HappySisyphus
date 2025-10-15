#pragma once
#include <glm/glm.hpp>
#include <Sisyphus/Renderer/Camera.h>
#include <glm/ext/matrix_transform.hpp>

namespace Sisyphus {

    class PerspectiveCamera : public Camera {
    public:
        PerspectiveCamera(float fovY, float aspectRatio, float nearClip, float farClip);

        void SetProjection(float fovY, float aspectRatio, float nearClip, float farClip);

        inline void SetViewportSize(float width, float height) { m_AspectRatio = width / height; }

        void Zoom(float yoffset) {
            m_FOV -= (float)yoffset;
            if (m_FOV < 1.0f)
                m_FOV = 1.0f;
            if (m_FOV > 45.0f)
                m_FOV = 45.0f;

            UpdateProjectionMatrix();
        }


    private:
        void UpdateProjectionMatrix();

    private:
        float m_FOV, m_AspectRatio, m_NearClip, m_FarClip;
    };


    class FlyCamera : public PerspectiveCamera
    {
    public:
        FlyCamera(float fovY = 45.0f, float aspectRatio = 1280.0f / 720.0f, float nearClip = 0.1f, float farClip = 100.0f)
            : PerspectiveCamera(fovY, aspectRatio, nearClip, farClip),
            m_Position(3.0f, 3.0f, 3.0f),
            m_Front(0.0f, 0.0f, -1.0f),
            m_Yaw(-90.0f), m_Pitch(0.0f)
        {

            UpdateCameraVectors();
            ProcessRotation(-45.f, -45.f);
        }

        ~FlyCamera() = default;

        const glm::mat4& GetViewMatrix() const { return m_View; }

        void SetPosition(const glm::vec3& position) {
            m_Position = position;
            UpdateCameraVectors();
        }
        const glm::vec3 GetPosition() const { return m_Position; }
        glm::vec3 GetFront() const { return m_Front; }
      

        void ProcessRotation(float xoffset, float yoffset, bool constrainPitch = true) {
            m_Yaw += xoffset;
            m_Pitch += yoffset;

            if (constrainPitch) {
                if (m_Pitch > 89.0f) m_Pitch = 89.0f;
                if (m_Pitch < -89.0f) m_Pitch = -89.0f;
            }

            UpdateCameraVectors();
        }

        void ProcessMovement(const glm::vec3& direction, float deltaTime, float speed = 5.0f) {
            m_Position += direction * speed * deltaTime;
            UpdateCameraVectors();
        }

    private:
        void UpdateCameraVectors() {
            glm::vec3 front;
            front.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
            front.y = sin(glm::radians(m_Pitch));
            front.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
            m_Front = glm::normalize(front);

            // Recalculate right and up vectors
            glm::vec3 right = glm::normalize(glm::cross(m_Front, glm::vec3(0.0f, 1.0f, 0.0f)));
            m_Up = glm::normalize(glm::cross(right, m_Front));

            // Update view matrix
            m_View = glm::lookAt(m_Position, m_Position + m_Front, m_Up);
        }

    private:
        glm::vec3 m_Position;
        glm::vec3 m_Front;
        glm::vec3 m_Up;

        float m_Yaw;
        float m_Pitch;

        glm::mat4 m_View;
    };

}
