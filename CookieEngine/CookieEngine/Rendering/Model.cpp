#include "Model.h"
#include "../IO/AssetManager.h"

namespace cookie
{
	inline void Model::loadModel(std::string path)
	{
		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << '\n';
			return;
		}
		directory = path.substr(0, path.find_last_of('/'));
		processNode(scene->mRootNode, scene);
	}
	inline void Model::processNode(aiNode* node, const aiScene* scene)
	{
		for (int i = 0; i < node->mNumMeshes; i++)
		{
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
			meshes.push_back(processMesh(mesh, scene));
		}

		for (int i = 0; i < node->mNumChildren; i++)
		{
			processNode(node->mChildren[i], scene);
		}
	}
	inline Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene)
	{
		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;
		std::vector<Texture> textures;

		for (int i = 0; i < mesh->mNumVertices; i++)
		{
			Vertex vertex {};
			glm::vec3 vector {};

			vector.x = mesh->mVertices[i].x;
			vector.y = mesh->mVertices[i].y;
			vector.z = mesh->mVertices[i].z;
			vertex.Position = vector;

			vector.x = mesh->mNormals[i].x;
			vector.y = mesh->mNormals[i].y;
			vector.z = mesh->mNormals[i].z;
			vertex.Normal = vector;

			if (mesh->mTextureCoords[0])
			{
				vertex.TexCoords.x = mesh->mTextureCoords[0][i].x;
				vertex.TexCoords.y = mesh->mTextureCoords[0][i].y;
			}
			else
			{
				vertex.TexCoords = glm::vec2(0.0f);
			}
			vertices.push_back(vertex);
		}

		for (int i = 0; i < mesh->mNumFaces; i++)
		{
			aiFace face = mesh->mFaces[i];
			for (int j = 0; j < face.mNumIndices; j++)
			{
				indices.push_back(face.mIndices[j]);
			}
		}

		if (mesh->mMaterialIndex >= 0)
		{
			aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
			std::vector<Texture> diffuseMaps =
				loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
			textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

			std::vector<Texture> specularMaps =
				loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
			textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
		}
		return Mesh { vertices, indices, textures };
	}
	std::vector<Texture> Model::loadMaterialTextures(aiMaterial* mat, aiTextureType type,
		std::string typeName)
	{
		std::vector<Texture> result;
		for (int i = 0; i < mat->GetTextureCount(type); i++)
		{
			aiString str {};
			mat->GetTexture(type, i, &str);
			bool skip { false };
			for (int i = 0; i < loadedTextures.size(); i++)
			{
				if (std::strcmp(loadedTextures[i].Path.data(), str.C_Str()) == 0)
				{
					skip = true;
					result.push_back(loadedTextures[i]);
					break;
				}
			}
			if (!skip)
			{
				Texture texture {};
				texture.Id = AssetManager::TextureFromFile(str.C_Str(), directory);
				texture.Type = typeName;
				texture.Path = str.C_Str();
				result.push_back(texture);
				loadedTextures.push_back(texture);
			}
		}
		return move(result);
	}
}