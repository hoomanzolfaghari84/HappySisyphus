#include "hspch.h"

#include <filesystem>
#include "Application.h"
//#include "Sisyphus/Renderer/Renderer.h"

#include "Sisyphus/Utils/PlatformUtils.h"
#include <glad/glad.h>

#include "Sisyphus/Renderer/Shader.h"

namespace Sisyphus {

	Application* Application::s_Instance = nullptr;

	Application::Application(const ApplicationSpecification& specification)
		: m_Specification(specification)
	{

		/*HZ_PROFILE_FUNCTION();*/

		SP_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		// Set working directory here
		if (!m_Specification.WorkingDirectory.empty())
			std::filesystem::current_path(m_Specification.WorkingDirectory);

		SIPH_CORE_INFO("working Directory: {}", m_Specification.WorkingDirectory);

		m_Window = Window::Create(WindowProps(m_Specification.Name));
		m_Window->SetEventCallback(SP_BIND_EVENT_FN(Application::OnEvent));

		//Renderer::Init();

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

		SIPH_CORE_TRACE("Engine App Initialized");

		m_VertexArray = VertexArray::Create();

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.f,
			0.5f, -0.5f, 0.0f,  0.2f, 0.3f, 0.8f, 1.f,
			0.0f, 0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.f
		};

		m_VertexBuffer = VertexBuffer::Create(vertices, sizeof(vertices));

		
		BufferLayout layout = {
			{ ShaderDataType::Float3, "a_Position"},
			{ ShaderDataType::Float4, "a_Color"}
		};

		m_VertexBuffer->SetLayout(layout);

	
		m_VertexArray->AddVertexBuffer(m_VertexBuffer);


		unsigned int indices[3] = { 0,1,2 };
		m_IndexBuffer = IndexBuffer::Create(indices, sizeof(indices)/sizeof(uint32_t) );

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

			out vec3 v_Position;
			out vec4 v_Color;

			void main(){
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = vec4(a_Position, 1.0);
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

		m_Shader.reset(new Shader(vertexSrc, fragmentSrc));


	}

	Application::~Application()
	{
	}

	void Application::PushLayer(Layer* layer)
	{
		//HZ_PROFILE_FUNCTION();

		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* layer)
	{
		//HZ_PROFILE_FUNCTION();

		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}

	void Application::Run()
	{
		//HZ_PROFILE_FUNCTION();

		while (m_Running)
		{
			//HZ_PROFILE_SCOPE("RunLoop");

			m_Shader->Bind();
			m_VertexArray->Bind();
			glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);

			float time = Time::GetTime();
			Timestep timestep = time - m_LastFrameTime;
			m_LastFrameTime = time;

			//ExecuteMainThreadQueue();

			if (!m_Minimized)
			{
				{
					//HZ_PROFILE_SCOPE("LayerStack OnUpdate");

					for (Layer* layer : m_LayerStack)
						layer->OnUpdate(timestep);
				}

				m_ImGuiLayer->Begin();
				{
					//HZ_PROFILE_SCOPE("LayerStack OnImGuiRender");

					for (Layer* layer : m_LayerStack)
						layer->OnImGuiRender();
				}
				m_ImGuiLayer->End();
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
		//HZ_PROFILE_FUNCTION();

		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(SP_BIND_EVENT_FN(Application::OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(SP_BIND_EVENT_FN(Application::OnWindowResize));
		//SIPH_CORE_INFO("Event {}", e.GetName());
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
		//HZ_PROFILE_FUNCTION();

		if (e.GetWidth() == 0 || e.GetHeight() == 0)
		{
			m_Minimized = true;
			return false;
		}

		m_Minimized = false;
		//Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());

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

