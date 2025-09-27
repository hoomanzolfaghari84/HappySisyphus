#include "Sandbox3D.h"

#include <imgui/imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Sandbox3D::Sandbox3D() : Layer("Sandbox2D")
{
}

void Sandbox3D::OnAttach()
{
    m_Camera.SetPosition({ 0.0f, 0.0f, -10.0f }); // move back so we can see the cube

    std::vector<Sisyphus::Vertex> cubeVertices = {
        // positions            // normals           // texcoords
        
        // Back face (-Z)
        {{-0.5f,-0.5f,-0.5f}, {0,0,-1}, {0,0}},
        {{ 0.5f,-0.5f,-0.5f}, {0,0,-1}, {1,0}},
        {{ 0.5f, 0.5f,-0.5f}, {0,0,-1}, {1,1}},
        {{-0.5f, 0.5f,-0.5f}, {0,0,-1}, {0,1}},

        // Front face (+Z)
        {{-0.5f,-0.5f, 0.5f}, {0,0,1}, {0,0}},
        {{ 0.5f,-0.5f, 0.5f}, {0,0,1}, {1,0}},
        {{ 0.5f, 0.5f, 0.5f}, {0,0,1}, {1,1}},
        {{-0.5f, 0.5f, 0.5f}, {0,0,1}, {0,1}},

        // Left face (-X)
        {{-0.5f,-0.5f,-0.5f}, {-1,0,0}, {0,0}},
        {{-0.5f, 0.5f,-0.5f}, {-1,0,0}, {1,0}},
        {{-0.5f, 0.5f, 0.5f}, {-1,0,0}, {1,1}},
        {{-0.5f,-0.5f, 0.5f}, {-1,0,0}, {0,1}},

        // Right face (+X)
        {{ 0.5f,-0.5f,-0.5f}, {1,0,0}, {0,0}},
        {{ 0.5f, 0.5f,-0.5f}, {1,0,0}, {1,0}},
        {{ 0.5f, 0.5f, 0.5f}, {1,0,0}, {1,1}},
        {{ 0.5f,-0.5f, 0.5f}, {1,0,0}, {0,1}},

        // Bottom face (-Y)
        {{-0.5f,-0.5f,-0.5f}, {0,-1,0}, {0,0}},
        {{ 0.5f,-0.5f,-0.5f}, {0,-1,0}, {1,0}},
        {{ 0.5f,-0.5f, 0.5f}, {0,-1,0}, {1,1}},
        {{-0.5f,-0.5f, 0.5f}, {0,-1,0}, {0,1}},

        // Top face (+Y)
        {{-0.5f, 0.5f,-0.5f}, {0,1,0}, {0,0}},
        {{ 0.5f, 0.5f,-0.5f}, {0,1,0}, {1,0}},
        {{ 0.5f, 0.5f, 0.5f}, {0,1,0}, {1,1}},
        {{-0.5f, 0.5f, 0.5f}, {0,1,0}, {0,1}}
    };

    std::vector<uint32_t> cubeIndices = {
        0,1,2, 2,3,0,       // back
        4,5,6, 6,7,4,       // front
        8,9,10, 10,11,8,    // left
        12,13,14, 14,15,12, // right
        16,17,18, 18,19,16, // bottom
        20,21,22, 22,23,20  // top
    };

    m_CubeMesh = CreateRef<Sisyphus::Mesh>(cubeVertices, cubeIndices);

}

void Sandbox3D::OnDetach()
{
}

void Sandbox3D::OnUpdate(Sisyphus::Timestep ts)
{
	// Update

	
	// Render

	Sisyphus::RenderCommand::SetClearColor({ 0.1, 0.1, 0.1, 1.0 });
	Sisyphus::RenderCommand::Clear();


    /*Sisyphus::Renderer3D::BeginScene(m_Camera);
    glm::mat4 cubeTransform = glm::translate(glm::mat4(1.0f), { 0.0f, 0.0f, 0.0f });
    Sisyphus::Renderer3D::DrawMesh(m_CubeMesh, cubeTransform);
    Sisyphus::Renderer3D::EndScene();*/


    /*float m_AspectRatio = 1280.f / 720.f;
    Sisyphus::Renderer2D::BeginScene(Sisyphus::OrthographicCamera(-m_AspectRatio * 1.f, m_AspectRatio * 1.f, -1.f, 1.f));

    Sisyphus::Renderer2D::DrawQuad({ -1.f, 0.f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
    Sisyphus::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });


    Sisyphus::Renderer2D::EndScene();*/

}

void Sandbox3D::OnImGuiRender()
{

}

void Sandbox3D::OnEvent(Sisyphus::Event& e)
{

}
