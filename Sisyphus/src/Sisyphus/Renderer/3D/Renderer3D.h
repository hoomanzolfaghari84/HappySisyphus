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

        static void DrawMesh(const Ref<Mesh>& mesh, const glm::mat4& transform, const glm::vec3 lightPosition); 
        static void DrawLight(const Ref<Mesh>& mesh, const glm::mat4& transform);
        static TextureLibrary* GetTextureLibrary() {
            return s_TextureLibrary;
        }
    private:
        struct SceneData {
            glm::mat4 ViewMatrix;
            glm::mat4 ProjectionMatrix;
            glm::vec3 CameraPosition;

            static const uint32_t MaxVertices = 4 * 20000;
            static const uint32_t MaxIndices = 6 * 20000;
            static const uint32_t MaxTextureSlots = 32; // TODO: RenderCaps

            std::array<Ref<Texture2D>, MaxTextureSlots> TextureSlots;
            uint32_t TextureSlotIndex = 1; // 0 = white texture
            Ref<Texture2D> WhiteTexture;

        };
        static SceneData* s_SceneData;
        static ShaderLibrary* s_ShaderLibrary;
        static TextureLibrary* s_TextureLibrary;

    };

}
