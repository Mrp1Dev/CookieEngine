#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

namespace cookie
{
	struct Transform
	{
		glm::vec3 position;
		glm::vec3 scale;
		glm::fquat rotation;
	};
}