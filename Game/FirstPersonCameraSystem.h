#pragma once
#include "ECS/World.h"
#include <Rendering/CameraData.h>
#include <Rendering/TransformData.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../CookieEngine/CookieEngine/Resources.h"
#include "FirstPersonControllerData.h"

class FirstPersonCameraSystem : public ck::System
{
public:
	void Update(ck::World* world) override;
	void FixedUpdate(ck::World* world) override;
};
