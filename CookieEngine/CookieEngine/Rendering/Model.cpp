#include "Model.h"
#include "../IO/AssetManager.h"

namespace cookie
{
	void Model::loadModel(std::string path)
	{
		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenNormals);

		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << '\n';
			return;
		}
		directory = path.substr(0, path.find_last_of('/'));
		processNode(scene->mRootNode, scene);
		setupBoundingBoxValues();
	}
	void Model::processNode(aiNode* node, const aiScene* scene)
	{
		for (unsigned int i = 0; i < node->mNumMeshes; i++)
		{
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
			meshes.push_back(processMesh(mesh, scene));
		}

		for (unsigned int i = 0; i < node->mNumChildren; i++)
		{
			processNode(node->mChildren[i], scene);
		}
	}
	Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene)
	{
		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;
		std::vector<Texture> textures;

		for (unsigned int i = 0; i < mesh->mNumVertices; i++)
		{
			Vertex vertex {};
			glm::vec3 vector {};

			vector.x = mesh->mVertices[i].x;
			vector.y = mesh->mVertices[i].y;
			vector.z = mesh->mVertices[i].z;
			vertex.position = vector;

			vector.x = mesh->mNormals[i].x;
			vector.y = mesh->mNormals[i].y;
			vector.z = mesh->mNormals[i].z;
			vertex.normal = vector;

			if (mesh->mTextureCoords[0])
			{
				vertex.texCoords.x = mesh->mTextureCoords[0][i].x;
				vertex.texCoords.y = mesh->mTextureCoords[0][i].y;
			}
			else
			{
				vertex.texCoords = glm::vec2(0.0f);
			}
			vertices.push_back(vertex);
		}

		for (unsigned int i = 0; i < mesh->mNumFaces; i++)
		{
			aiFace face = mesh->mFaces[i];
			for (unsigned int j = 0; j < face.mNumIndices; j++)
			{
				indices.push_back(face.mIndices[j]);
			}
		}

		if (mesh->mMaterialIndex >= 0)
		{
			aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
			std::vector<Texture> diffuseMaps =
				loadMaterialTextures(material, aiTextureType_DIFFUSE, TextureType::Diffuse);
			textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

			std::vector<Texture> specularMaps =
				loadMaterialTextures(material, aiTextureType_SPECULAR, TextureType::Specular);
			textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
		}
		return Mesh { vertices, indices, textures };
	}
	std::vector<Texture> Model::loadMaterialTextures(aiMaterial* mat,
		aiTextureType type, TextureType typeName)
	{
		std::vector<Texture> result;
		for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
		{
			aiString str {};
			mat->GetTexture(type, i, &str);
			bool skip { false };
			for (int i = 0; i < loadedTextures.size(); i++)
			{
				if (std::strcmp(loadedTextures[i].path.data(), str.C_Str()) == 0)
				{
					skip = true;
					result.push_back(loadedTextures[i]);
					break;
				}
			}
			if (!skip)
			{
				Texture texture {};
				texture.id = AssetManager::TextureFromFile(str.C_Str(), directory);
				texture.type = typeName;
				texture.path = str.C_Str();
				result.push_back(texture);
				loadedTextures.push_back(texture);
			}
		}
		return move(result);
	}

	void Model::setupBoundingBoxValues()
	{
		glm::vec3 min {};
		glm::vec3 max {};
		for (auto& mesh : meshes)
		{
			auto pos = mesh.boundingBoxMin;
			if (pos.x < min.x) min.x = pos.x;
			if (pos.y < min.y) min.y = pos.y;
			if (pos.z < min.z) min.z = pos.z;
			pos = mesh.boundingBoxMax;
			if (pos.x > max.x) max.x = pos.x;
			if (pos.y > max.y) max.y = pos.y;
			if (pos.z > max.z) max.z = pos.z;
		}
		boundingBoxMin = min;
		boundingBoxMax = max;
	}
}