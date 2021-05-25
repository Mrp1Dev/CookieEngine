#pragma once
#include <string>
namespace cookie
{
	namespace ShaderUniforms
	{
		const std::string_view MODEL_MATRIX = "ModelMatrix";
		const std::string_view VIEW_MATRIX = "ViewMatrix";
		const std::string_view PROJECTION_MATRIX = "ProjectionMatrix";
		const std::string_view PROJECTION_VIEW_MATRIX = "ProjectionViewMatrix";
		const std::string_view BASE_COLOR = "Material.baseColor";
		const std::string_view DIFFUSE_TEXTURE_ARRAY = "Material.diffuseTextures";
		const std::string_view SPECULAR_TEXTURE_ARRAY = "Material.specularTextures";
		const std::string_view DIFFUSE_TEXTURE_COUNT = "Material.diffuseTextureCount";
		const std::string_view SPECULAR_TEXTURE_COUNT = "Material.specularTextureCount";
		namespace DirectionalLight
		{
			const std::string_view DIRECTION = "DirectionalLight.direction";
			const std::string_view AMBIENT_COLOR = "DirectionalLight.ambientColor";
			const std::string_view DIFFUSE_COLOR = "DirectionalLight.diffuseColor";
			const std::string_view SPECULAR_COLOR = "DirectionalLight.specularColor";
		}
		namespace PointLight
		{
			constexpr std::string_view Position(int i)
			{
				return "PointLights[" + std::to_string(i) + "].position";
			}

			constexpr std::string_view DiffuseColor(int i)
			{
				return "PointLights[" + std::to_string(i) + "].diffuseColor";
			}

			constexpr std::string_view SpecularColor(int i)
			{
				return "PointLights[" + std::to_string(i) + "].specularColor";
			}

			const std::string_view LIGHT_COUNT = "PointLightCount";
		}
	}
}