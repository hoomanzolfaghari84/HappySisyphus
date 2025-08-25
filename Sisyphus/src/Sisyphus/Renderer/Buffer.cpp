#include "hspch.h"
#include "Buffer.h"



#include "Sisyphus/Renderer/Renderer.h"

#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Sisyphus {

	std::shared_ptr<VertexBuffer> VertexBuffer::Create(uint32_t size)
	{
		//return std::make_shared<OpenGLVertexBuffer>(size);
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    SP_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return std::make_shared<OpenGLVertexBuffer>(size);
		}

		SP_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	std::shared_ptr<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t size)
	{
		//return std::make_shared<OpenGLVertexBuffer>(vertices, size);
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    SP_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return std::make_shared<OpenGLVertexBuffer>(vertices, size);
		}

		SP_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	std::shared_ptr<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t size)
	{
		//return std::make_shared<OpenGLIndexBuffer>(indices, size);
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    SP_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return std::make_shared<OpenGLIndexBuffer>(indices, size);
		}

		SP_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}