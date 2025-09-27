#pragma once

#include "Sisyphus/Renderer/Mesh.h"
#include "Sisyphus/Renderer/Shader.h"
#include "Sisyphus/Renderer/Camera.h"
#include "Sisyphus/Renderer/PerspectiveCamera.h"

namespace Sisyphus {

    class Renderer3D {
    public:
        static void Init();
        static void Shutdown();

        static void BeginScene(const Camera& camera, const glm::mat4& cameraTransform);
        static void BeginScene(const PerspectiveCamera& camera);
        static void EndScene();

        static void DrawMesh(const Ref<Mesh>& mesh, const glm::mat4& transform);

    private:
        struct SceneData {
            glm::mat4 ViewProjectionMatrix;
        };
        static SceneData* s_SceneData;
    };

}
