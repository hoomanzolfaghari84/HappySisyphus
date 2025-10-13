#include "hspch.h"

#include "Materials.h"

namespace Sisyphus {

    static std::string TextureTypeToString(TextureType type)
    {
        switch (type)
        {
        case TextureType::Diffuse:   return "Diffuse";
        case TextureType::Specular:  return "Specular";
        case TextureType::Normal:    return "Normal";
        case TextureType::Metallic:  return "Metallic";
        case TextureType::Roughness: return "Roughness";
        case TextureType::AO:        return "Ambient Occlusion";
        case TextureType::Emissive:  return "Emissive";
        default:                     return "Unknown";
        }
    }

    void Material::PrintInfo() const
    {
        std::cout << "========== Material Info ==========\n";

        std::cout << "Flat Color: (" << std::fixed << std::setprecision(3)
            << m_FlatColor.r << ", " << m_FlatColor.g << ", "
            << m_FlatColor.b << ", " << m_FlatColor.a << ")\n";

        std::cout << "Shininess: " << m_Shininess << "\n";

        std::cout << "\n-- Textures --\n";
        if (m_Textures.empty())
        {
            std::cout << "No textures assigned.\n";
        }
        else
        {
            for (const auto& [type, texture] : m_Textures)
            {
                std::cout << "  " << TextureTypeToString(type) << ": ";
                if (texture)
                {
                    std::cout << (texture->GetPath().empty() ? "(No file path)" : texture->GetPath()) << "\n";
                }
                else
                {
                    std::cout << "nullptr\n";
                }
            }
        }

        std::cout << "===================================\n";
    }

    void Material::Bind(const Ref<Shader>& shader) const
    {
        uint32_t slot = 0;

        for (auto& [type, tex] : m_Textures)
        {
            if (tex)
            {
                tex->Bind(slot);

                std::string uniformName;
                switch (type)
                {
                case TextureType::Diffuse:   uniformName = "u_Material.diffuse";   break;
                case TextureType::Specular:  uniformName = "u_Material.specular";  break;
                case TextureType::Normal:    uniformName = "u_Material.normal";    break;
                case TextureType::Metallic:  uniformName = "u_Material.metallic";  break;
                case TextureType::Roughness: uniformName = "u_Material.roughness"; break;
                case TextureType::AO:        uniformName = "u_Material.ao";        break;
                case TextureType::Emissive:  uniformName = "u_Material.emissive";  break;
                default:                     uniformName = "u_Material.unknown";   break;
                }

                shader->SetInt(uniformName, slot);
                slot++;
            }
            //else
            //{
            //    // If no texture, upload fallback color
            //    std::string colorUniform;
            //    switch (type)
            //    {
            //    case TextureType::Diffuse:  colorUniform = "u_Material.DiffuseColor"; break;
            //    case TextureType::Specular: colorUniform = "u_Material.SpecularColor"; break;
            //        // ... and so on
            //    default: continue;
            //    }
            //    shader->SetFloat4(colorUniform, prop.Value);
            //}
        }
        shader->SetFloat4("u_Material.flatColor", m_FlatColor);
        shader->SetFloat("u_Material.shininess", m_Shininess);
    }

}