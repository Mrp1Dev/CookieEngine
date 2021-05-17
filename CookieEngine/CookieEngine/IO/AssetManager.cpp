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
}