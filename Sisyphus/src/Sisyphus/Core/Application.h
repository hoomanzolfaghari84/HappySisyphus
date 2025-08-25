#pragma once

#include "Sisyphus/Core/Base.h"

#include "Sisyphus/Core/Window.h"
#include "Sisyphus/Core/LayerStack.h"
#include "Sisyphus/Events/Event.h"
#include "Sisyphus/Events/ApplicationEvent.h"

#include "Sisyphus/Core/Timestep.h"

#include "Sisyphus/ImGui/ImGuiLayer.h"

#include "Sisyphus/Renderer/Shader.h"
#include <Sisyphus/Renderer/Buffer.h>
#include <Sisyphus/Renderer/VertexArray.h>

int main(int argc, char** argv);

namespace Sisyphus {

	struct SISYPHUS_API ApplicationCommandLineArgs
	{
		int Count = 0;
		char** Args = nullptr;

		const char* operator[](int index) const
		{
			SP_CORE_ASSERT(index < Count, "Index out of range for Application Commandline Args");
			return Args[index];
		}
	};

	struct SISYPHUS_API ApplicationSpecification
	{
		std::string Name = "Sisyphus Application";
		std::string WorkingDirectory;
		ApplicationCommandLineArgs CommandLineArgs;
	};

	class SISYPHUS_API Application
	{
	public:
		Application(const ApplicationSpecification& specification);
		virtual ~Application();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		Window& GetWindow() { return *m_Window; }

		void Close();

		ImGuiLayer* GetImGuiLayer() { return m_ImGuiLayer; }

		static Application& Get() { return *s_Instance; }

		const ApplicationSpecification& GetSpecification() const { return m_Specification; }

		//void SubmitToMainThread(const std::function<void()>& function);
	private:
		void Run();
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);

		//void ExecuteMainThreadQueue();
	private:
		ApplicationSpecification m_Specification;
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		bool m_Minimized = false;
		LayerStack m_LayerStack;
		float m_LastFrameTime = 0.0f;

		std::unique_ptr<Shader> m_Shader;
		std::shared_ptr<VertexArray> m_VertexArray;
		std::shared_ptr<VertexBuffer> m_VertexBuffer;
		std::shared_ptr<IndexBuffer> m_IndexBuffer;


		std::shared_ptr<VertexArray> m_SquareVA;
		/*std::shared_ptr<VertexBuffer> m_VertexBuffer;
		std::shared_ptr<IndexBuffer> m_IndexBuffer;*/

		/*std::vector<std::function<void()>> m_MainThreadQueue;
		std::mutex m_MainThreadQueueMutex;*/
	private:
		static Application* s_Instance;
		friend int ::main(int argc, char** argv);
	};

	// To be defined in CLIENT
	Application* CreateApplication(ApplicationCommandLineArgs args);

}


