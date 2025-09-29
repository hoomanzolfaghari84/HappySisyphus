#include "hspch.h"
#include "Renderer3D.h"
#include "Sisyphus/Renderer/RenderCommand.h"
#include "Sisyphus/Renderer/3D/PerspectiveCamera.h"
#include "Sisyphus/Renderer/3D/Mesh.h"

namespace Sisyphus {

    Renderer3D::SceneData* Renderer3D::s_SceneData = nullptr;
    ShaderLibrary* Renderer3D::s_ShaderLibrary = nullptr;

    

    void Renderer3D::Init()
    {
        s_SceneData = new SceneData();
        s_ShaderLibrary = new ShaderLibrary();

        // Load a very simple shader
        s_ShaderLibrary->Load("assets/shaders/Basic3D.glsl");
        s_ShaderLibrary->Load("assets/shaders/LightSrc.glsl");
    }

    void Renderer3D::Shutdown()
    {
        delete s_SceneData;
    }

   
    void Renderer3D::BeginScene(const FlyCamera& camera)
    {
        s_SceneData->ViewMatrix = camera.GetViewMatrix();
        s_SceneData->ProjectionMatrix = camera.GetProjection();
        
    }

    void Renderer3D::EndScene()
    {
    }

    void Renderer3D::DrawMesh(const Ref<Mesh>& mesh, const glm::mat4& transform,
        const glm::vec4 color, const glm::vec3 lightPosition)
    {

        auto shader = s_ShaderLibrary->Get("Basic3D");
        shader->Bind();
        shader->SetMat4("u_Model", transform);
        shader->SetMat4("u_View", s_SceneData->ViewMatrix);
        shader->SetMat4("u_Projection", s_SceneData->ProjectionMatrix);
        shader->SetFloat4("u_ObjectColor", color);
        shader->SetFloat3("u_LightColor", glm::vec3(1.f,1.f,1.f));
        shader->SetFloat3("u_LightPos", lightPosition);


        RenderCommand::DrawIndexed(mesh->GetVertexArray());
    }

    void Renderer3D::DrawLight(const Ref<Mesh>& mesh, const glm::mat4& transform) {
        auto shader = s_ShaderLibrary->Get("LightSrc");

        shader->Bind();
        shader->SetMat4("u_Model", transform);
        shader->SetMat4("u_View", s_SceneData->ViewMatrix);
        shader->SetMat4("u_Projection", s_SceneData->ProjectionMatrix);

        RenderCommand::DrawIndexed(mesh->GetVertexArray());

       
        

    }
}
