#pragma once
#include <string>
#include <array>
namespace cookie
{
	namespace ShaderUniforms
	{
		const std::string_view MODEL_MATRIX = "ModelMatrix";
		const std::string_view VIEW_MATRIX = "ViewMatrix";
		const std::string_view PROJECTION_MATRIX = "ProjectionMatrix";
		const std::string_view PROJECTION_VIEW_MATRIX = "ProjectionViewMatrix";
		const std::string_view INV_MODEL_MATRIX = "InvModelMatrix";
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
			constexpr int MAX_COUNT = 8;
			const std::array<std::string_view, MAX_COUNT> POSITIONS {
				"PointLights[0].position",
				"PointLights[1].position",
				"PointLights[2].position",
				"PointLights[3].position",
				"PointLights[4].position",
				"PointLights[5].position",
				"PointLights[6].position",
				"PointLights[7].position",
			};

			const std::array<std::string_view, MAX_COUNT> DIFFUSE_COLORS {
				"PointLights[0].diffuseColor",
				"PointLights[1].diffuseColor",
				"PointLights[2].diffuseColor",
				"PointLights[3].diffuseColor",
				"PointLights[4].diffuseColor",
				"PointLights[5].diffuseColor",
				"PointLights[6].diffuseColor",
				"PointLights[7].diffuseColor",
			};

			const std::array<std::string_view, MAX_COUNT> SPECULAR_COLORS {
				"PointLights[0].specularColor",
				"PointLights[1].specularColor",
				"PointLights[2].specularColor",
				"PointLights[3].specularColor",
				"PointLights[4].specularColor",
				"PointLights[5].specularColor",
				"PointLights[6].specularColor",
				"PointLights[7].specularColor",
			};

			const std::array<std::string_view, MAX_COUNT> RANGES {
				"PointLights[0].range",
				"PointLights[1].range",
				"PointLights[2].range",
				"PointLights[3].range",
				"PointLights[4].range",
				"PointLights[5].range",
				"PointLights[6].range",
				"PointLights[7].range",
			};

			const std::array<std::string_view, MAX_COUNT> DIFFUSE_STRENGTHS {
				"PointLights[0].diffuseStrength",
				"PointLights[1].diffuseStrength",
				"PointLights[2].diffuseStrength",
				"PointLights[3].diffuseStrength",
				"PointLights[4].diffuseStrength",
				"PointLights[5].diffuseStrength",
				"PointLights[6].diffuseStrength",
				"PointLights[7].diffuseStrength",
			};


			const std::array<std::string_view, MAX_COUNT> SPECULAR_STRENGTHS {
				"PointLights[0].specularStrength",
				"PointLights[1].specularStrength",
				"PointLights[2].specularStrength",
				"PointLights[3].specularStrength",
				"PointLights[4].specularStrength",
				"PointLights[5].specularStrength",
				"PointLights[6].specularStrength",
				"PointLights[7].specularStrength",
			};

			const std::string_view LIGHT_COUNT = "PointLightCount";
		}
	}
}