#include "hspch.h"
#include "Mesh.h"
#include "Sisyphus/Renderer/Renderer.h"

namespace Sisyphus {

    void Mesh::PrintInfo() const
    {
        std::cout << "========== Mesh Info ==========\n";
        std::cout << "Vertex Count: " << m_Vertices.size() << "\n";
        std::cout << "Index Count:  " << m_Indices.size() << "\n";

        if (m_Material)
			m_Material->PrintInfo();
        else
            std::cout << "Material: None\n";

        std::cout << "\n-- Vertices --\n";
        for (size_t i = 0; i < m_Vertices.size(); ++i)
        {
            const auto& v = m_Vertices[i];
            std::cout << "Vertex " << i << ":\n";
            std::cout << "  Position: (" << std::fixed << std::setprecision(3)
                << v.Position.x << ", " << v.Position.y << ", " << v.Position.z << ")\n";
            std::cout << "  Normal:   (" << v.Normal.x << ", " << v.Normal.y << ", " << v.Normal.z << ")\n";
            std::cout << "  TexCoords:(" << v.TexCoords.x << ", " << v.TexCoords.y << ")\n";
        }

        std::cout << "-- Indices --\n";
        for (size_t i = 0; i < m_Indices.size(); ++i)
        {
            std::cout << m_Indices[i];
            if ((i + 1) % 3 == 0)
                std::cout << "\n"; // assume triangles
            else
                std::cout << ", ";
        }

        std::cout << "===============================\n";
    }

    // --- Vector-based constructors ---

    Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, Ref<Material> material)
        : m_Vertices(std::move(vertices)), m_Indices(std::move(indices)), m_Material(material)
    {
        SetupBuffers();
    }

    Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices)
        : m_Vertices(std::move(vertices)), m_Indices(std::move(indices))
    {
        SetupBuffers();
        m_Material = CreateRef<Material>();
    }

    // --- Raw float-based constructor ---
    Mesh::Mesh(float* vertices, uint32_t vertexBufferSizeInBytes, uint32_t* indices, uint32_t indexCount)
    {

        m_VertexArray = VertexArray::Create();

        m_VertexBuffer = VertexBuffer::Create(vertices, vertexBufferSizeInBytes);
        m_VertexBuffer->SetLayout({
            { ShaderDataType::Float3,           "a_Position"     },
            { Sisyphus::ShaderDataType::Float3, "a_Normal"       },
            { ShaderDataType::Float2,           "a_TexCoords"    },
            });

        m_VertexArray->AddVertexBuffer(m_VertexBuffer);

        m_IndexBuffer = IndexBuffer::Create(indices, indexCount);
        m_VertexArray->SetIndexBuffer(m_IndexBuffer);

        m_Material = CreateRef<Material>();
    }

    // --- SetupBuffers helper ---
    void Mesh::SetupBuffers()
    {
        m_VertexArray = VertexArray::Create();

        m_VertexBuffer = VertexBuffer::Create(
            m_Vertices.data(),
            static_cast<uint32_t>(m_Vertices.size() * sizeof(Vertex))
        );

        m_VertexBuffer->SetLayout({
            { Sisyphus::ShaderDataType::Float3, "a_Position" },
            { Sisyphus::ShaderDataType::Float3, "a_Normal" },
            { Sisyphus::ShaderDataType::Float2, "a_TexCoords" }
            });

        m_VertexArray->AddVertexBuffer(m_VertexBuffer);

        m_IndexBuffer = IndexBuffer::Create(
            m_Indices.data(),
            static_cast<uint32_t>(m_Indices.size())
        );

        m_VertexArray->SetIndexBuffer(m_IndexBuffer);
    }

} // namespace Sisyphus
