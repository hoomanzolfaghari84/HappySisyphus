#include "hspch.h"
#include "Renderer3D.h"
#include "Sisyphus/Renderer/RenderCommand.h"

namespace Sisyphus {

    Renderer3D::SceneData* Renderer3D::s_SceneData = nullptr;
    static Ref<Shader> s_Shader;

    void Renderer3D::Init()
    {
        s_SceneData = new SceneData();

        // Load a very simple shader
        s_Shader = Shader::Create("assets/shaders/Basic3D.glsl");
    }

    void Renderer3D::Shutdown()
    {
        delete s_SceneData;
    }

    void Renderer3D::BeginScene(const Camera& camera, const glm::mat4& cameraTransform)
    {
        s_SceneData->ViewProjectionMatrix =
            camera.GetProjection() * glm::inverse(cameraTransform);
        /*s_Shader->Bind();
        s_Shader->SetMat4("u_ViewProjection", s_SceneData->ViewProjectionMatrix);*/
    }

    void Renderer3D::BeginScene(const PerspectiveCamera& camera)
    {
        s_SceneData->ViewProjectionMatrix = camera.GetViewProjection();
        /*s_Shader->Bind();
        s_Shader->SetMat4("u_ViewProjection", s_SceneData->ViewProjectionMatrix);*/
    }

    void Renderer3D::EndScene()
    {
    }

    void Renderer3D::DrawMesh(const Ref<Mesh>& mesh, const glm::mat4& transform)
    {
        s_Shader->Bind();
        s_Shader->SetMat4("u_ViewProjection", s_SceneData->ViewProjectionMatrix);
        s_Shader->SetMat4("u_Transform", transform);
        s_Shader->SetFloat3("u_LightDir", glm::normalize(glm::vec3(-0.5f, -1.0f, -0.3f)));
        s_Shader->SetFloat3("u_Color", glm::vec3(0.8f, 0.2f, 0.3f));

        mesh->GetVertexArray()->Bind();
        RenderCommand::DrawIndexed(mesh->GetVertexArray());
    }

}
