#pragma once
#include <glm/glm.hpp>
namespace cookie
{
	struct DirectionalLightData
	{
		glm::vec3 direction {};
		glm::vec3 color { };
		glm::vec3 ambientColor {};
	};
}