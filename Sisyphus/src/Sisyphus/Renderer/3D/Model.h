#pragma once

#include "Sisyphus/Renderer/3D/Mesh.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace Sisyphus {

    class Model
    {
    public:
        Model(std::string const& path)
        {
            LoadModel(path);
        }
    
        std::vector<Ref<Mesh>> GetMeshes()
        {
            return m_Meshes;
        }
    private:
        // model data
        std::vector<Ref<Mesh>> m_Meshes;
        std::vector<Ref<Material>> m_Materials;
        std::string directory;

        void LoadModel(std::string path);
        void ProcessNode(aiNode* node, const aiScene* scene);
        Ref<Mesh> ProcessMesh(aiMesh* mesh, const aiScene* scene);
        Ref<Material> ProcessMaterial(aiMaterial* material);
    };

}

