#pragma once

#include "Sisyphus/Renderer/3D/Mesh.h"
#include "Sisyphus/Renderer/Shader.h"
#include "Sisyphus/Renderer/Camera.h"
#include "Sisyphus/Renderer/3D/PerspectiveCamera.h"

namespace Sisyphus {

    class Renderer3D {
    public:
        static void Init();
        static void Shutdown();

        static void BeginScene(const FlyCamera& camera);
        static void EndScene();

        static void DrawMesh(const Ref<Mesh>& mesh, const glm::mat4& transform, const glm::vec4 color, const glm::vec3 lightPosition); 
        static void DrawLight(const Ref<Mesh>& mesh, const glm::mat4& transform);

    private:
        struct SceneData {
            glm::mat4 ViewMatrix;
            glm::mat4 ProjectionMatrix;
        };
        static SceneData* s_SceneData;
        static ShaderLibrary* s_ShaderLibrary;

    };

}
