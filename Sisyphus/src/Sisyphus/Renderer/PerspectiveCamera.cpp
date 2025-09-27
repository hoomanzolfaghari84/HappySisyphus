#include "hspch.h"
#include "PerspectiveCamera.h"
#include <glm/gtc/matrix_transform.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/euler_angles.hpp>


namespace Sisyphus {

    PerspectiveCamera::PerspectiveCamera(float fovY, float aspectRatio, float nearClip, float farClip)
        : m_FOV(fovY), m_AspectRatio(aspectRatio), m_NearClip(nearClip), m_FarClip(farClip)
    {
        SetProjection(fovY, aspectRatio, nearClip, farClip);
        RecalculateViewMatrix();
    }

    void PerspectiveCamera::SetProjection(float fovY, float aspectRatio, float nearClip, float farClip)
    {
        m_FOV = fovY;
        m_AspectRatio = aspectRatio;
        m_NearClip = nearClip;
        m_FarClip = farClip;
        m_Projection = glm::perspective(glm::radians(m_FOV), m_AspectRatio, m_NearClip, m_FarClip);
        m_ViewProjectionMatrix = m_Projection * m_ViewMatrix;
    }

    void PerspectiveCamera::RecalculateViewMatrix()
    {
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position)
            * glm::yawPitchRoll(glm::radians(m_Rotation.y), glm::radians(m_Rotation.x), glm::radians(m_Rotation.z));

        m_ViewMatrix = glm::inverse(transform);
        m_ViewProjectionMatrix = m_Projection * m_ViewMatrix;
    }

}