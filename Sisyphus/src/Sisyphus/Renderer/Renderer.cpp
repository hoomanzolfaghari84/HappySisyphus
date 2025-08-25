#include "hspch.h"
#include "Renderer.h"
//#include "Sisyphus/Renderer/Renderer2D.h"

namespace Sisyphus {

	std::unique_ptr<Renderer::SceneData> Renderer::s_SceneData = std::unique_ptr<Renderer::SceneData>();

	void Renderer::Init()
	{
		//HZ_PROFILE_FUNCTION();
		s_SceneData = std::make_unique<SceneData>(); // not in Hazel
		RenderCommand::Init();
		//Renderer2D::Init();
	}

	void Renderer::Shutdown()
	{
		//Renderer2D::Shutdown();
	}

	void Renderer::OnWindowResize(uint32_t width, uint32_t height)
	{
		RenderCommand::SetViewport(0, 0, width, height);
	}

	void Renderer::BeginScene(OrthographicCamera& camera)
	{

		if (!s_SceneData)
		{
			std::cerr << "Renderer::BeginScene called before Renderer::Init!" << std::endl;
			return;
		}

		s_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
	}

	void Renderer::EndScene()
	{
	}

	void Renderer::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray, const glm::mat4& transform)
	{
		shader->Bind();
		shader->UploadUniformMat4("u_ViewProjection", s_SceneData->ViewProjectionMatrix);
		/*shader->SetMat4("u_ViewProjection", s_SceneData->ViewProjectionMatrix);
		shader->SetMat4("u_Transform", transform);*/

		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}

}
