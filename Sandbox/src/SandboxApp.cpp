#include <iostream>

#include <Sisyphus.h>
// -------- Entry Point --------------
#include "Sisyphus/Core/EntryPoint.h"
// -----------------------------------

#include "Sandbox2D.h"

#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class ExampleLayer : public Sisyphus::Layer {

public:
	ExampleLayer() : Layer("Example"), m_CameraController(1280.f/720.f, true), m_TrianglePosition(0.f) {

		m_VertexArray = Sisyphus::VertexArray::Create();

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};

		Sisyphus::Ref<Sisyphus::VertexBuffer> vertexBuffer = Sisyphus::VertexBuffer::Create(vertices, sizeof(vertices));

		Sisyphus::BufferLayout layout = {
			{Sisyphus::ShaderDataType::Float3, "a_Position"},
			{Sisyphus::ShaderDataType::Float4, "a_Color"}
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);


		unsigned int indices[3] = { 0,1,2 };
		Sisyphus::Ref<Sisyphus::IndexBuffer> indexBuffer = Sisyphus::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));
		m_VertexArray->SetIndexBuffer(indexBuffer);		

		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}
		)";

		m_Shader = Sisyphus::Shader::Create("VertexPosColor", vertexSrc, fragmentSrc);


		// Square


		m_SquareVA = Sisyphus::VertexArray::Create();


		float squareVertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.f , 0.f,
			 0.5f, -0.5f, 0.0f, 1.f , 0.f,
			 0.5f,  0.5f, 0.0f, 1.f , 1.f,
			-0.5f,  0.5f, 0.0f, 0.f , 1.f
		};

		Sisyphus::Ref<Sisyphus::VertexBuffer> squareVB = Sisyphus::VertexBuffer::Create(squareVertices, sizeof(squareVertices));
		squareVB->SetLayout({
			{ Sisyphus::ShaderDataType::Float3, "a_Position" },
			{ Sisyphus::ShaderDataType::Float2, "a_TexCoord" }
			});
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		Sisyphus::Ref<Sisyphus::IndexBuffer> squareIB;
		squareIB = Sisyphus::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));
		m_SquareVA->SetIndexBuffer(squareIB);

		std::string flatColorShaderVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
			}
		)";

		std::string flatColorShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			
			uniform vec3 u_Color;

			void main()
			{
				color = vec4(u_Color, 1.0);
			}
		)";

		m_FlatColorShader = Sisyphus::Shader::Create("FlatColor", flatColorShaderVertexSrc, flatColorShaderFragmentSrc);


		// Texture

		auto textureShader = m_ShaderLibrary.Load("assets/shaders/Texture.glsl");


		m_Texture = Sisyphus::Texture2D::Create("assets/textures/Checkerboard.png");
		m_HSLogoTexture = Sisyphus::Texture2D::Create("assets/textures/HSLogo.png");


		textureShader->Bind();
		textureShader->SetInt("u_Texture", 0);
		
		

	}

	void OnUpdate(Sisyphus::Timestep ts) override {
		
		// Update

		m_CameraController.OnUpdate(ts);

		if (Sisyphus::Input::IsKeyPressed(Sisyphus::Key::A)) {
			m_TrianglePosition.x -= m_TriangleMoveSpeed * ts;
		}

		else if (Sisyphus::Input::IsKeyPressed(Sisyphus::Key::D)) {
			m_TrianglePosition.x += m_TriangleMoveSpeed * ts;
		}

		if (Sisyphus::Input::IsKeyPressed(Sisyphus::Key::S)) {
			m_TrianglePosition.y -= m_TriangleMoveSpeed * ts;
		}

		else if (Sisyphus::Input::IsKeyPressed(Sisyphus::Key::W)) {
			m_TrianglePosition.y += m_TriangleMoveSpeed * ts;
		}
		

		// Render

		Sisyphus::RenderCommand::SetClearColor({ 0.1, 0.1, 0.1, 1.0 });
		Sisyphus::RenderCommand::Clear();

	
		Sisyphus::Renderer::BeginScene(m_CameraController.GetCamera());


		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		m_FlatColorShader->Bind();
		m_FlatColorShader->SetFloat3("u_Color", m_SquareColor);


		for (int y = 0; y < 20; y++)
		{
			for (int x = 0; x < 20; x++)
			{
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				Sisyphus::Renderer::Submit(m_FlatColorShader, m_SquareVA, transform);
			}
		}



		auto textureShader = m_ShaderLibrary.Get("Texture");
		
		m_Texture->Bind();
		Sisyphus::Renderer::Submit(textureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5)));

		m_HSLogoTexture->Bind();
		Sisyphus::Renderer::Submit(textureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5)) );

		


		// Triangle
		//glm::mat4 transform = glm::translate(glm::mat4(1.f), m_TrianglePosition);
		//Sisyphus::Renderer::Submit(m_Shader, m_VertexArray, transform);



		Sisyphus::Renderer::EndScene();

	}

	void OnImGuiRender() override {
		ImGui::Begin("Settings");

		ImGui::ColorEdit3("Squares Color", glm::value_ptr(m_SquareColor));

		ImGui::End();
	}

	void OnEvent(Sisyphus::Event& e) override {
		m_CameraController.OnEvent(e);

		
	}
	
	

private:
	Sisyphus::ShaderLibrary m_ShaderLibrary;

	Sisyphus::Ref<Sisyphus::Shader> m_Shader;
	Sisyphus::Ref<Sisyphus::VertexArray> m_VertexArray;

	Sisyphus::Ref<Sisyphus::Texture2D> m_Texture, m_HSLogoTexture;

	Sisyphus::Ref<Sisyphus::Shader> m_FlatColorShader;
	Sisyphus::Ref<Sisyphus::VertexArray> m_SquareVA;

	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };

	Sisyphus::OrthographicCameraController m_CameraController;

	glm::vec3 m_TrianglePosition;
	float m_TriangleMoveSpeed = 1.5f;
};


class SandboxApp : public Sisyphus::Application
{

public:
	SandboxApp(const Sisyphus::ApplicationSpecification& specification)
		: Sisyphus::Application(specification)
	{
		//PushLayer(new ExampleLayer());
		PushLayer(new Sandbox2D());
		SIPH_TRACE("Sandbox App Initialized");
	}

	~SandboxApp()
	{

	}
};


Sisyphus::Application* Sisyphus::CreateApplication(Sisyphus::ApplicationCommandLineArgs args)
{
	ApplicationSpecification spec;
	spec.Name = "Sandbox";
	spec.WorkingDirectory = "";//"../Boulder";
	spec.CommandLineArgs = args;

	return new SandboxApp(spec);
}