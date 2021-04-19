#include "Model.h"
#include "../IO/AssetManager.h"

namespace cookie
{
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