#include "AssetManager.h"

namespace cookie
{
	std::unordered_map<std::string, Model> AssetManager::models {};
	std::unordered_map<std::pair<std::string, std::string>, Shader, PairHash> AssetManager::shaders {};
	const std::string ASSETS_PATH = "../../Game/Assets/";

	ShaderData AssetManager::GetShader(const std::string vertexShaderPath, const std::string fragmentShaderPath)
	{
		auto existing = AssetManager::shaders.find({ vertexShaderPath, fragmentShaderPath });
		if (existing != AssetManager::shaders.end())
		{
			return ShaderData { &existing->second };
		}
		return ShaderData {
			&AssetManager::shaders.insert(
				std::pair {
					std::pair{
					vertexShaderPath, fragmentShaderPath
				},
				Shader(
					(ASSETS_PATH + vertexShaderPath).c_str(),
					(ASSETS_PATH + fragmentShaderPath).c_str()
				)
				}
			).first->second
		};
	}
	ModelRendererData AssetManager::GetModel(const std::string path, bool active)
	{
		auto existing = AssetManager::models.find(path);
		if (existing != AssetManager::models.end())
		{
			return ModelRendererData { &existing->second, active };
		}
		return ModelRendererData {
			&AssetManager::models.insert(
				std::pair {
					path, Model(ASSETS_PATH + path)
				}
			).first->second, active
		};
	}
	unsigned int AssetManager::TextureFromFile(const char* path, const std::string& directory, bool flip)
	{
		stbi_set_flip_vertically_on_load(flip);
		std::string filename = std::string(path);
		filename = directory + '/' + filename;

		unsigned int textureID;
		glGenTextures(1, &textureID);

		int width, height, nrComponents;
		unsigned char* data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
		if (data)
		{
			GLenum format;
			if (nrComponents == 1)
				format = GL_RED;
			else if (nrComponents == 3)
				format = GL_RGB;
			else if (nrComponents == 4)
				format = GL_RGBA;

			glBindTexture(GL_TEXTURE_2D, textureID);
			glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			stbi_image_free(data);
		}
		else
		{
			std::cerr << "Texture failed to load at path: " << path << std::endl;
			stbi_image_free(data);
		}
		return textureID;
	}

}