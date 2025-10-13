#include "hspch.h"
#include "Renderer3D.h"
#include "Sisyphus/Renderer/RenderCommand.h"
#include "Sisyphus/Renderer/3D/PerspectiveCamera.h"
#include "Sisyphus/Renderer/3D/Mesh.h"

namespace Sisyphus {

    Renderer3D::SceneData* Renderer3D::s_SceneData = nullptr;
    ShaderLibrary* Renderer3D::s_ShaderLibrary = nullptr;
    TextureLibrary* Renderer3D::s_TextureLibrary = nullptr;

    

    void Renderer3D::Init()
    {
        s_SceneData = new SceneData();
        s_ShaderLibrary = new ShaderLibrary();
        s_TextureLibrary = new TextureLibrary();

        // Load a very simple shader
        s_ShaderLibrary->Load("assets/shaders/Basic3D.glsl");
        s_ShaderLibrary->Load("assets/shaders/LightSrc.glsl");

        s_SceneData->WhiteTexture = Texture2D::Create(TextureSpecification());
        uint32_t whiteTextureData = 0xffffffff;
        s_SceneData->WhiteTexture->SetData(&whiteTextureData, sizeof(uint32_t));

        s_SceneData->TextureSlots[0] = s_SceneData->WhiteTexture;


    }

    void Renderer3D::Shutdown()
    {
        delete s_SceneData;
    }

   
    void Renderer3D::BeginScene(const FlyCamera& camera)
    {
        s_SceneData->ViewMatrix = camera.GetViewMatrix();
        s_SceneData->ProjectionMatrix = camera.GetProjection();
        s_SceneData->CameraPosition = camera.GetPosition();
        
    }

    void Renderer3D::EndScene()
    {
    }

    

    void Renderer3D::DrawMesh(const Ref<Mesh>& mesh, const glm::mat4& transform, const glm::vec3 lightPosition)
    {

        auto shader = s_ShaderLibrary->Get("Basic3D");
        shader->Bind();


        shader->SetMat4("u_Model", transform);
        shader->SetMat4("u_View", s_SceneData->ViewMatrix);
        shader->SetMat4("u_Projection", s_SceneData->ProjectionMatrix);


        shader->SetFloat3("u_ViewPos", s_SceneData->CameraPosition);

        mesh->GetMaterial()->Bind(shader);

        shader->SetFloat3("u_Light.position", lightPosition);
        shader->SetFloat3("u_Light.ambient", { 0.2f, 0.2f, 0.2f });
        shader->SetFloat3("u_Light.diffuse", { 0.5f, 0.5f, 0.5f });
        shader->SetFloat3("u_Light.specular",{ 1.0f, 1.0f, 1.0f });

        RenderCommand::DrawIndexed(mesh->GetVertexArray());

        shader->Unbind();
    }

    void Renderer3D::DrawLight(const Ref<Mesh>& mesh, const glm::mat4& transform) {
        auto shader = s_ShaderLibrary->Get("LightSrc");

        shader->Bind();
        shader->SetMat4("u_Model", transform);
        shader->SetMat4("u_View", s_SceneData->ViewMatrix);
        shader->SetMat4("u_Projection", s_SceneData->ProjectionMatrix);

        RenderCommand::DrawIndexed(mesh->GetVertexArray());

        shader->Unbind();
        
    }
}
