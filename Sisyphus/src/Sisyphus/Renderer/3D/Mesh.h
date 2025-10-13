#pragma once

#include "Sisyphus/Renderer/VertexArray.h"
#include "Sisyphus/Renderer/Shader.h"
#include "Sisyphus/Core/Base.h"
#include "Sisyphus/Renderer/Texture.h"
#include "Materials.h"

namespace Sisyphus {

    struct Vertex {
        glm::vec3 Position;
        glm::vec3 Normal;
        glm::vec2 TexCoords;     
    };

    class Mesh {
    public:
        // Vector-based constructors (used for imported or procedural meshes)
        Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, Ref<Material> material);
        Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices);

        // Raw float-based constructor (used for simple primitives)
        Mesh(float* vertices, uint32_t vertexBufferSizeInBytes, uint32_t* indices, uint32_t indexCount);

        Ref<VertexArray> GetVertexArray() const { return m_VertexArray; }

        void SetMaterial(Ref<Material> material) {
            m_Material = material;
        }
        Ref<Material> GetMaterial() {
            return m_Material;
        }

        size_t GetVertexCount()
        {
            return m_Vertices.size();
		}

        void PrintInfo() const;
    private:
        void SetupBuffers();

    private:
        // Mesh data
        std::vector<Vertex>       m_Vertices;
        std::vector<unsigned int> m_Indices;
        Ref<Material> m_Material;

        // GPU buffers
        Ref<VertexArray>  m_VertexArray;
        Ref<VertexBuffer> m_VertexBuffer;
        Ref<IndexBuffer>  m_IndexBuffer;
    };

} // namespace Sisyphus
