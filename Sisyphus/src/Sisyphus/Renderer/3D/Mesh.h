#pragma once

#include "Sisyphus/Renderer/VertexArray.h"
#include "Sisyphus/Renderer/Shader.h"
#include "Sisyphus/Core/Base.h"

namespace Sisyphus {
    

    struct Vertex
    {
        glm::vec3 Position;
        glm::vec3 Normal;
    };
        // Ensure the struct is tightly packed (no compiler padding)
//#ifdef _MSC_VER
//#pragma pack(push, 1)
//#endif
//
//    // For GCC/Clang
//    } 
//#ifndef _MSC_VER
//    __attribute__((packed));
//#else
//    ;
//#endif // !_MSC_VER
//    
//#ifdef _MSC_VER
//#pragma pack(pop)
//#endif

    class Mesh {
    public:
        Mesh(float* vertices, uint32_t vertexCount, uint32_t* indices, uint32_t indexCount);

        Ref<VertexArray> GetVertexArray() const { return m_VertexArray; }

    private:
        Ref<VertexArray> m_VertexArray;
        Ref<VertexBuffer> m_VertexBuffer;
        Ref<IndexBuffer> m_IndexBuffer;
    };

}
