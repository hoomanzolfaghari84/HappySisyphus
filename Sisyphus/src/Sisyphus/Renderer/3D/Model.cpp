#include "hspch.h"
#include "Model.h"
#include "Sisyphus/Renderer/3D/Renderer3D.h"

namespace Sisyphus {
	void Model::LoadModel(std::string path)
	{
		Assimp::Importer importer;
		const aiScene* scene =
			importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

		
		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
			return;
		}
		directory = path.substr(0, path.find_last_of('/'));

		std::cout << "Meshes: " << scene->mNumMeshes << "\n";
		for (size_t i = 0; i < scene->mNumMeshes; ++i) {
			aiMesh* mesh = scene->mMeshes[i];
			std::cout << "Mesh " << i
				<< " | Vertices: " << mesh->mNumVertices
				<< " | Faces: " << mesh->mNumFaces
				<< " | Normals: " << (mesh->HasNormals() ? "yes" : "no")
				<< " | TexCoords: " << (mesh->HasTextureCoords(0) ? "yes" : "no")
				<< "\n";
		}

		ProcessNode(scene->mRootNode, scene);
	}

	void Model::ProcessNode(aiNode* node, const aiScene* scene)
	{

		for (size_t i = 0; i < node->mNumMeshes; i++)
		{
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
			m_Meshes.push_back(ProcessMesh(mesh, scene));
			SIPH_CORE_INFO("Loaded Mesh");
		}

		for (size_t i = 0; i < node->mNumChildren; i++)
		{
			ProcessNode(node->mChildren[i], scene);
		}
	}

	Ref<Mesh> Model::ProcessMesh(aiMesh* mesh, const aiScene* scene)
	{
		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;

		for (unsigned int i = 0; i < mesh->mNumVertices; i++)
		{
			Vertex vertex;
			// process vertex positions, normals and texture coordinates
			glm::vec3 vector;
			vector.x = mesh->mVertices[i].x;
			vector.y = mesh->mVertices[i].y;
			vector.z = mesh->mVertices[i].z;
			vertex.Position = vector;

			vector.x = mesh->mNormals[i].x;
			vector.y = mesh->mNormals[i].y;
			vector.z = mesh->mNormals[i].z;
			vertex.Normal = vector;

			if (mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
			{
				glm::vec2 vec;
				vec.x = mesh->mTextureCoords[0][i].x;
				vec.y = mesh->mTextureCoords[0][i].y;
				vertex.TexCoords = vec;
			}
			else
				vertex.TexCoords = glm::vec2(0.0f, 0.0f);

			vertices.push_back(vertex);

		}

		// process indices
		for (unsigned int i = 0; i < mesh->mNumFaces; i++)
		{
			aiFace face = mesh->mFaces[i];
			for (unsigned int j = 0; j < face.mNumIndices; j++)
				indices.push_back(face.mIndices[j]);
		}


		// process material
		if (mesh->mMaterialIndex >= 0)
		{
			aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
			Ref<Material> mat = ProcessMaterial(material);
			return CreateRef<Mesh>(vertices, indices, mat);

		}else return CreateRef<Mesh>(vertices, indices);

	}

	Ref<Material> Model::ProcessMaterial(aiMaterial* material)
	{
		std::string matName = material->GetName().C_Str();
		//auto mat = MaterialLibrary::CreateOrGet(matName, shader);
		auto mat = CreateRef<Material>();

		auto loadTextures = [&](aiTextureType type, TextureType ourType) {
			for (unsigned int i = 0; i < material->GetTextureCount(type); i++) {
				aiString str;
				material->GetTexture(type, i, &str);
				std::string fullPath = directory + "/" + str.C_Str();
				mat->SetTexture(ourType, Renderer3D::GetTextureLibrary()->Load(fullPath));
			}
			};

		loadTextures(aiTextureType_DIFFUSE, TextureType::Diffuse);
		loadTextures(aiTextureType_SPECULAR, TextureType::Specular);
		loadTextures(aiTextureType_NORMALS, TextureType::Normal);
		loadTextures(aiTextureType_METALNESS, TextureType::Metallic);
		loadTextures(aiTextureType_DIFFUSE_ROUGHNESS, TextureType::Roughness);
		loadTextures(aiTextureType_AMBIENT_OCCLUSION, TextureType::AO);

		return mat;
	}
	 
}