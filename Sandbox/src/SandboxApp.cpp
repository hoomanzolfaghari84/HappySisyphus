#include <iostream>
#include <Sisyphus.h>
#include <glm/gtc/matrix_transform.hpp>

class ExampleLayer : public Sisyphus::Layer {

public:
	ExampleLayer() : Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.f), m_TrianglePosition(0.f) {

		m_VertexArray = Sisyphus::VertexArray::Create();

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.f,
			0.5f, -0.5f, 0.0f,  0.2f, 0.3f, 0.8f, 1.f,
			0.0f, 0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.f
		};

		m_VertexBuffer = Sisyphus::VertexBuffer::Create(vertices, sizeof(vertices));


		Sisyphus::BufferLayout layout = {
			{Sisyphus::ShaderDataType::Float3, "a_Position"},
			{ Sisyphus::ShaderDataType::Float4, "a_Color"}
		};

		m_VertexBuffer->SetLayout(layout);


		m_VertexArray->AddVertexBuffer(m_VertexBuffer);


		unsigned int indices[3] = { 0,1,2 };
		m_IndexBuffer = Sisyphus::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));

		m_VertexArray->SetIndexBuffer(m_IndexBuffer);



		/*m_SquareVA = VertexArray::Create();


		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f,
			0.5f, -0.5f, 0.0f,
			0.0f, 0.5f, 0.0f
		};

		std::shared_ptr<VertexBuffer> squareVB = VertexBuffer::Create();*/

		std::string vertexSrc = R"(
			#version 450 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Color;

			void main(){
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		
		)";

		std::string fragmentSrc = R"(
			#version 450 core
			
			layout(location = 0) out vec4 color;
			
			in vec3 v_Position;
			in vec4 v_Color;

			void main(){
				color = vec4((v_Position + 1)*0.5, 1.0);
				color = v_Color;
			}
		
		)";

		m_Shader = Sisyphus::Shader::Create("Traingle Shader", vertexSrc, fragmentSrc);

	}

	void OnUpdate(Sisyphus::Timestep ts) override {


		if (Sisyphus::Input::IsKeyPressed( Sisyphus::Key::Left )) {
			m_CameraPosition.x -= m_CameraMoveSpeed * ts;
		}

		else if (Sisyphus::Input::IsKeyPressed( Sisyphus::Key::Right)) {
			m_CameraPosition.x += m_CameraMoveSpeed * ts;
		}

		if (Sisyphus::Input::IsKeyPressed( Sisyphus::Key::Down )) {
			m_CameraPosition.y -= m_CameraMoveSpeed * ts;
		}

		else if (Sisyphus::Input::IsKeyPressed( Sisyphus::Key::Up   )){
			m_CameraPosition.y += m_CameraMoveSpeed * ts;
		}



		if (Sisyphus::Input::IsKeyPressed(Sisyphus::Key::Q)) {
			m_CameraRotation += m_CameraRotationSpeed * ts;
		}
		else if(Sisyphus::Input::IsKeyPressed(Sisyphus::Key::E))
		{
			m_CameraRotation -= m_CameraRotationSpeed * ts;

		}


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
		

		Sisyphus::RenderCommand::SetClearColor({ 0.1, 0.1, 0.1, 1.0 });
		Sisyphus::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		glm::mat4 transform = glm::translate(glm::mat4(1.f), m_TrianglePosition);

		Sisyphus::Renderer::BeginScene(m_Camera);

		Sisyphus::Renderer::Submit(m_Shader, m_VertexArray, transform);

		Sisyphus::Renderer::EndScene();

	}

	void OnImGuiRender() override {

	}

	void OnEvent(Sisyphus::Event& event) override {

	}
	
	

private:
	std::shared_ptr<Sisyphus::Shader> m_Shader;
	std::shared_ptr<Sisyphus::VertexArray> m_VertexArray;
	std::shared_ptr<Sisyphus::VertexBuffer> m_VertexBuffer;
	std::shared_ptr<Sisyphus::IndexBuffer> m_IndexBuffer;

	std::shared_ptr<Sisyphus::VertexArray> m_SquareVA;

	Sisyphus::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraMoveSpeed = 1.f;
	float m_CameraRotationSpeed = 10.f;
	float m_CameraRotation = 0.f;

	glm::vec3 m_TrianglePosition;
	float m_TriangleMoveSpeed = 1.5f;
};


class SandboxApp : public Sisyphus::Application
{

public:
	SandboxApp(const Sisyphus::ApplicationSpecification& specification)
		: Sisyphus::Application(specification)
	{
		PushLayer(new ExampleLayer());
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
	spec.WorkingDirectory = "../Boulder";
	spec.CommandLineArgs = args;

	return new SandboxApp(spec);
}