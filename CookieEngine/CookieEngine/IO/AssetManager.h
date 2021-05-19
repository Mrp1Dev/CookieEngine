#pragma once
#include "../Rendering/Model.h"
#include <cookie/stb_image.h>
#include <unordered_map>
#include "../Rendering/ModelRendererData.h"
#include "../Rendering/ShaderData.h"
namespace cookie
{
	struct PairHash
	{
		template <class T1, class T2>
		std::size_t operator() (const std::pair<T1, T2>& pair) const
		{
			return (std::hash<T1>()(pair.first) * 327423) ^ std::hash<T2>()(pair.second);
		}
	};
	class AssetManager
	{
	public:
		static std::unordered_map<std::string, Model> models;
		static std::unordered_map<std::pair<std::string, std::string>, Shader, PairHash> shaders;

		static unsigned int TextureFromFile(const char* path, const std::string& directory, bool flip = false)
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
		static ModelRendererData GetModel(const std::string path, bool active = true);

		static ShaderData GetShader(const std::string vertexShaderPath, const std::string fragmentShaderPath);
	};

}