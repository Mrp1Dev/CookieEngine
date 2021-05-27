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

		static u32 TextureFromFile(const char* path, const std::string& directory, bool flip = false);
		
		static ModelRendererData GetModel(const std::string path, bool active = true);

		static ShaderData GetShader(const std::string vertexShaderPath, const std::string fragmentShaderPath);
	};

}