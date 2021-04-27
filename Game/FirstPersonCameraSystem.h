#pragma once
#include "ECS/World.h"
#include <Rendering/CameraData.h>
#include <Rendering/TransformData.h>

class FirstPersonCameraSystem : public ck::System
{
public:
	virtual void Update(ck::World* world) override
	{
		auto cameraQuery { world->QueryEntities<ck::CameraData, ck::TransformData>() };
		cameraQuery->Foreach([](ck::CameraData& camera, ck::TransformData& transform)
			{
				transform.position -= glm::vec3(0, 0, 1) * 1.0f / 100.0f;
				transform.rotation = glm::rotate(transform.rotation, glm::radians(-1.0f), transform.rotation * glm::vec3(1, 0, 0));
			});
	}
};
