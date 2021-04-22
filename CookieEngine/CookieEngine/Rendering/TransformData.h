#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
namespace cookie
{
	struct TransformData
	{
		glm::vec3 position {};
		glm::vec3 scale;
		glm::fquat rotation;

	};
}