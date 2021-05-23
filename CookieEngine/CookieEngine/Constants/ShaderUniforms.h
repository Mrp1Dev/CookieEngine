#pragma once
#include <string>
namespace cookie
{
	namespace ShaderUniforms
	{
		const std::string MODEL_MATRIX = "ModelMatrix";
		const std::string VIEW_MATRIX = "ViewMatrix";
		const std::string PROJECTION_MATRIX = "ProjectionMatrix";
		const std::string PROJECTION_VIEW_MATRIX = "ProjectionViewMatrix";
		const std::string BASE_COLOR = "Material.baseColor";
		const std::string DIFFUSE_TEXTURE_ARRAY = "Material.diffuseTextures";
		const std::string SPECULAR_TEXTURE_ARRAY = "Material.specularTextures";
		const std::string DIFFUSE_TEXTURE_COUNT = "Material.diffuseTextureCount";
		const std::string SPECULAR_TEXTURE_COUNT = "Material.specularTextureCount";
	}
}