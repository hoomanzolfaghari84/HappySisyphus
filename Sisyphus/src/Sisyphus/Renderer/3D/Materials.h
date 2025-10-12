#pragma once

#include "glm/glm.hpp"
#include "Sisyphus/Renderer/Texture.h"
#include <Sisyphus/Renderer/Shader.h>

namespace Sisyphus {

	enum class TextureType {
		Diffuse,
		Specular,
		Normal,
		Metallic,
		Roughness,
		AO,
		Emissive,
		Unknown
	};

    class Material {
    public:
        Material() = default;

        void SetTexture(TextureType type, const Ref<Texture>& texture) {
            m_Textures[type] = texture;
        }

        /*void SetColor(TextureType type, const glm::vec4& color) {
            m_Textures[type].Value = color;
        }*/

        void SetFlatColor(const glm::vec4& color) {
            m_FlatColor = color;
        }

        bool HasTexture(TextureType type) const {
            auto it = m_Textures.find(type);
            return it != m_Textures.end() && it->second;
        }

        Ref<Texture> GetTexture(TextureType type) const {
            auto it = m_Textures.find(type);
            return (it != m_Textures.end()) ? it->second : nullptr;
        }

        glm::vec4 GetFlatColor() const {
            return m_FlatColor;
        }

        float& GetShininess() { return m_Shininess; }
        const float& GetShininess() const { return m_Shininess; }
        void SetShininess(float shininess)
        {
            m_Shininess = shininess;
        }

        // Binding for rendering
        void Bind(const Ref<Shader>& shader) const;

        void PrintInfo() const;
    private:
        std::unordered_map<TextureType, Ref<Texture>> m_Textures;
        float m_Shininess = 1.0f;
        glm::vec4 m_FlatColor = glm::vec4(1.0f);
    };

}
