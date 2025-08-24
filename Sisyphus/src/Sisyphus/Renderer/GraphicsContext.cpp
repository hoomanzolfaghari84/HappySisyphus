#include "hspch.h"
#include "GraphicsContext.h"

#include "Sisyphus/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLContext.h"

namespace Sisyphus {

	std::shared_ptr<GraphicsContext> GraphicsContext::Create(void* window)
	{
		return std::make_shared<OpenGLContext>(static_cast<GLFWwindow*>(window));
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    SP_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return std::make_shared<OpenGLContext>(static_cast<GLFWwindow*>(window));
		}

		SP_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}