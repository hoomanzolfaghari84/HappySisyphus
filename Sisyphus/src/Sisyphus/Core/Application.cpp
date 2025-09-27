#include "hspch.h"

#include <filesystem>
#include "Application.h"
#include "Sisyphus/Renderer/Renderer.h"

#include "Sisyphus/Utils/PlatformUtils.h"

#include "Sisyphus/Renderer/Shader.h"

// Temp for 3d testing
#include "glad/glad.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Sisyphus {

	Application* Application::s_Instance = nullptr;

	Application::Application(const ApplicationSpecification& specification)
		: m_Specification(specification)
	{
		HS_PROFILE_FUNCTION();

		SP_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		// Set working directory here
		if (!m_Specification.WorkingDirectory.empty())
			std::filesystem::current_path(m_Specification.WorkingDirectory);

		SIPH_CORE_INFO("working Directory: {}", std::filesystem::current_path().string());

		m_Window = Window::Create(WindowProps(m_Specification.Name));
		m_Window->SetEventCallback(SP_BIND_EVENT_FN(Application::OnEvent));

		Renderer::Init();

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

		SIPH_CORE_TRACE("Engine App Initialized");

	}

	Application::~Application()
	{
	}

	void Application::PushLayer(Layer* layer)
	{
		HS_PROFILE_FUNCTION();

		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* layer)
	{
		HS_PROFILE_FUNCTION();

		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}
	

	

	void Application::Run()
	{
		HS_PROFILE_FUNCTION();

		while (m_Running)
		{
			HS_PROFILE_SCOPE("RunLoop");

			float time = Time::GetTime();
			Timestep timestep = time - m_LastFrameTime;
			m_LastFrameTime = time;

			//ExecuteMainThreadQueue();
		

			if (!m_Minimized)
			{
				{
					HS_PROFILE_SCOPE("LayerStack OnUpdate");

					for (Layer* layer : m_LayerStack)
						layer->OnUpdate(timestep);
				}

				m_ImGuiLayer->Begin();
				{
					HS_PROFILE_SCOPE("LayerStack OnImGuiRender");

					for (Layer* layer : m_LayerStack)
						layer->OnImGuiRender();
				}
				m_ImGuiLayer->End();
			}

			//3D Testing
			{
				static bool initialized = false;
				static Ref<VertexBuffer> cubeVBO;
				static Ref<VertexArray> cubeVAO;
				static Ref<Shader> cubeShader = nullptr;

				if (!initialized)
				{

					cubeVAO = VertexArray::Create();

					// Cube vertices: positions + normals
					float cubeVertices[] = {
						// positions          // normals
						-0.5f, -0.5f, -0.5f,   0.0f,  0.0f, -1.0f, // 0
						 0.5f, -0.5f, -0.5f,   0.0f,  0.0f, -1.0f, // 1
						 0.5f,  0.5f, -0.5f,   0.0f,  0.0f, -1.0f, // 2
						-0.5f,  0.5f, -0.5f,   0.0f,  0.0f, -1.0f, // 3

						-0.5f, -0.5f,  0.5f,   0.0f,  0.0f,  1.0f, // 4
						 0.5f, -0.5f,  0.5f,   0.0f,  0.0f,  1.0f, // 5
						 0.5f,  0.5f,  0.5f,   0.0f,  0.0f,  1.0f, // 6
						-0.5f,  0.5f,  0.5f,   0.0f,  0.0f,  1.0f, // 7
					};

					uint32_t cubeIndices[] = {
						// back face
						0, 1, 2, 2, 3, 0,
						// front face
						4, 5, 6, 6, 7, 4,
						// left face
						0, 3, 7, 7, 4, 0,
						// right face
						1, 5, 6, 6, 2, 1,
						// bottom face
						0, 1, 5, 5, 4, 0,
						// top face
						3, 2, 6, 6, 7, 3
					};

					cubeVBO = VertexBuffer::Create(cubeVertices, sizeof(cubeVertices));
					cubeVBO->SetLayout({
						{ ShaderDataType::Float3, "aPos" },
						{ ShaderDataType::Float3, "aNormal" }
						});

					cubeVAO->AddVertexBuffer(cubeVBO);

					auto cubeIBO = IndexBuffer::Create(cubeIndices, sizeof(cubeIndices) / sizeof(uint32_t));
					cubeVAO->SetIndexBuffer(cubeIBO);

					//glGenVertexArrays(1, &VAO);
					//glGenBuffers(1, &VBO);

					//glBindVertexArray(VAO);

					//glBindBuffer(GL_ARRAY_BUFFER, VBO);
					//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

					// position
					//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
					//glEnableVertexAttribArray(0);
					// normal
					//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
					//glEnableVertexAttribArray(1);

					// Create shader
					cubeShader = Shader::Create("assets/shaders/Test.glsl");

					initialized = true;
				}

				// Draw cube
				cubeShader->Bind();

				// Camera/View/Projection
				glm::mat4 projection = glm::perspective(glm::radians(45.0f),
					(float)m_Window->GetWidth() / (float)m_Window->GetHeight(),
					0.1f, 100.0f);
				glm::mat4 view = glm::lookAt(glm::vec3(2.0f, 2.0f, 2.0f), // Camera position
					glm::vec3(0.0f, 0.0f, 0.0f), // Look at origin
					glm::vec3(0.0f, 1.0f, 0.0f)); // Up vector
				glm::mat4 model = glm::mat4(1.0f); // Cube at origin

				cubeShader->Bind();
				cubeShader->SetMat4("model", model);
				cubeShader->SetMat4("view", view);
				cubeShader->SetMat4("projection", projection);

				// Light & color
				cubeShader->SetFloat3("lightPos", glm::vec3(3.0f, 3.0f, 3.0f));
				cubeShader->SetFloat3("viewPos", glm::vec3(2.0f, 2.0f, 2.0f));
				cubeShader->SetFloat3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
				cubeShader->SetFloat3("objectColor", glm::vec3(0.8f, 0.3f, 0.2f));

				cubeVAO->Bind();
				RenderCommand::DrawIndexed(cubeVAO);
			}

			m_Window->OnUpdate();
		}
	}

	void Application::Close()
	{
		m_Running = false;
	}

	/*void Application::SubmitToMainThread(const std::function<void()>& function)
	{
		std::scoped_lock<std::mutex> lock(m_MainThreadQueueMutex);

		m_MainThreadQueue.emplace_back(function);
	}*/

	void Application::OnEvent(Event& e)
	{
		HS_PROFILE_FUNCTION();

		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(SP_BIND_EVENT_FN(Application::OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(SP_BIND_EVENT_FN(Application::OnWindowResize));

		for (auto it = m_LayerStack.rbegin(); it != m_LayerStack.rend(); ++it)
		{
			if (e.Handled)
				break;
			(*it)->OnEvent(e);
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		HS_PROFILE_FUNCTION();

		if (e.GetWidth() == 0 || e.GetHeight() == 0)
		{
			m_Minimized = true;
			return false;
		}

		m_Minimized = false;
		Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());

		return false;
	}

	/*void Application::ExecuteMainThreadQueue()
	{
		std::scoped_lock<std::mutex> lock(m_MainThreadQueueMutex);

		for (auto& func : m_MainThreadQueue)
			func();

		m_MainThreadQueue.clear();
	}*/

}

