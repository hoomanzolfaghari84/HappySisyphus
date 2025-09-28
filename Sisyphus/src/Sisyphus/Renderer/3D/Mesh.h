#pragma once

#include "Sisyphus/Renderer/VertexArray.h"
#include "Sisyphus/Renderer/Shader.h"
#include "Sisyphus/Core/Base.h"

namespace Sisyphus {

    struct Vertex {
        glm::vec3 Position;
        glm::vec3 Normal;
        glm::vec2 TexCoord;
    };

    class Mesh {
    public:
        Mesh(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices);

        Ref<VertexArray> GetVertexArray() const { return m_VertexArray; }

    private:
        Ref<VertexArray> m_VertexArray;
    };

}
