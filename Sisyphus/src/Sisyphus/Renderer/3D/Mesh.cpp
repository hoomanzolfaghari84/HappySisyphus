#include "hspch.h"
#include "Mesh.h"
#include "Sisyphus/Renderer/Renderer.h"

namespace Sisyphus {

    Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices)
    {
        m_VertexArray = VertexArray::Create();

        Ref<VertexBuffer> vertexBuffer = VertexBuffer::Create(
            (vertices.size() * sizeof(Vertex))
        );
        vertexBuffer->SetLayout({
            { ShaderDataType::Float3, "a_Position" },
            { ShaderDataType::Float3, "a_Normal" },
            { ShaderDataType::Float2, "a_TexCoord" }
            });

        vertexBuffer->SetData(
            vertices.data(),
            (vertices.size() * sizeof(Vertex)
            ));

        m_VertexArray->AddVertexBuffer(vertexBuffer);

        Ref<IndexBuffer> indexBuffer = IndexBuffer::Create(
            (uint32_t*)indices.data(),
            (uint32_t)indices.size()
        );
        m_VertexArray->SetIndexBuffer(indexBuffer);
    }

}
