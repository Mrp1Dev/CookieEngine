#pragma once
#include "../Rendering/TransformData.h"
namespace cookie
{
	namespace math
	{
		void ToAngleAxis(glm::fquat quat, glm::vec3* axis, float* angle)
		{
			auto quatNormalized = glm::normalize(quat);
			*angle = 2 * acos(quatNormalized.w);
			float s = sqrt(1 - quatNormalized.w * quat.w);
			if (s <= 0.001f)
			{
				axis->x = quatNormalized.x;
				axis->y = quatNormalized.y;
				axis->z = quatNormalized.z;
			}
			else
			{
				axis->x = quatNormalized.x / s;
				axis->y = quatNormalized.y / s;
				axis->z = quatNormalized.z / s;
			}
		}
	}
}