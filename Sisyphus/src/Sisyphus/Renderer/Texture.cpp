#include "hspch.h"
#include "Texture.h"

#include "Sisyphus/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"

namespace Sisyphus {

	Ref<Texture2D> Texture2D::Create(const TextureSpecification& specification)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    SP_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return CreateRef<OpenGLTexture2D>(specification);
		}

		SP_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	Ref<Texture2D> Texture2D::Create(const std::string& path)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    SP_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return CreateRef<OpenGLTexture2D>(path);
		}

		SP_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	// ---- Texture Library ----

	void TextureLibrary::Add(const std::string& name, const Ref<Texture>& texture)
	{
		//SP_CORE_ASSERT(!Exists(name), "Texture already exists!");
		if (Exists(name)) return;
		m_Textures[name] = texture;
	}

	void TextureLibrary::Add(const Ref<Texture>& texture)
	{
		auto& name = texture->GetName();
		Add(name, texture);
	}
	Ref<Texture> TextureLibrary::Load(const std::string& filepath)
	{
		auto texture = Texture2D::Create(filepath);
		Add(texture);
		return texture;
	}
	Ref<Texture> TextureLibrary::Load(const std::string& name, const std::string& filepath)
	{
		auto texture = Texture2D::Create(filepath);
		Add(name, texture);
		return texture;
	}

	Ref<Texture> TextureLibrary::Get(const std::string& name)
	{
		SP_CORE_ASSERT(Exists(name), "Texture not found!");
		return m_Textures[name];
	}

	bool TextureLibrary::Exists(const std::string& name) const
	{
		return m_Textures.find(name) != m_Textures.end();
	}


}