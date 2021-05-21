#pragma once
#include "../ECS/World.h"
#include "ShaderData.h"
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "TransformData.h"
#include "CameraData.h"
#include "../ResourceTypes/Window.h"

namespace cookie
{
	class SetPerspectiveMatrixSystem : public System
	{
	public:
		virtual void Update(World* world) override;
	};
}