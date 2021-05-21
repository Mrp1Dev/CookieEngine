#pragma once
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <cookie/Shader.h>
#include "Mesh.h"

namespace cookie
{
	class Model
	{
	public:
		Model(std::string path)
		{
			loadModel(path);
		};

		std::vector<Mesh> meshes;
		std::vector<Texture> loadedTextures;
		std::string directory;
	private:
		void loadModel(std::string path);

		void processNode(aiNode* node, const aiScene* scene);

		Mesh processMesh(aiMesh* mesh, const aiScene* scene);

		std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type,
			std::string typeName);
	};
}