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
    }

    void PerspectiveCamera::SetProjection(float fovY, float aspectRatio, float nearClip, float farClip)
    {
        m_FOV = fovY;
        m_AspectRatio = aspectRatio;
        m_NearClip = nearClip;
        m_FarClip = farClip;
        UpdateProjectionMatrix();
    }

    void PerspectiveCamera::UpdateProjectionMatrix()
    {
        m_Projection = glm::perspective(glm::radians(m_FOV), m_AspectRatio, m_NearClip, m_FarClip);
    }



}