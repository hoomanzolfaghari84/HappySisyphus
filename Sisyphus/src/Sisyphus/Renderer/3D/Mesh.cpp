#include "hspch.h"
#include "Mesh.h"
#include "Sisyphus/Renderer/Renderer.h"

namespace Sisyphus {

    Mesh::Mesh(float* vertices, uint32_t size, uint32_t* indices, uint32_t indexCount)
    {
        m_VertexArray = VertexArray::Create();

        m_VertexBuffer = VertexBuffer::Create(
            vertices,
            size
        );
        SIPH_CORE_INFO("VertexBuffer created: {} bytes", size);
        m_VertexBuffer->SetLayout({
        { Sisyphus::ShaderDataType::Float3, "aPos" },
        { Sisyphus::ShaderDataType::Float3, "aNormal" }
            });


        const auto& layout = m_VertexBuffer->GetLayout();
        SIPH_CORE_INFO("BufferLayout stride: {}", layout.GetStride());
        for (auto& element : layout)
        {
            SIPH_CORE_INFO("Element: {} | Type: {} | Size: {} | Offset: {} | Components: {}",
                element.Name,
                (int)element.Type,
                element.Size,
                element.Offset,
                element.GetComponentCount()
            );
        }

        m_VertexArray->AddVertexBuffer(m_VertexBuffer);

        m_IndexBuffer = IndexBuffer::Create(
            indices,
            indexCount
        );
        m_VertexArray->SetIndexBuffer(m_IndexBuffer);


        
    }

}
