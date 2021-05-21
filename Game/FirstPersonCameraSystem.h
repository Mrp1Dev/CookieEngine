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
	ck::Input* input {};
public:
	virtual void Start(ck::World* world) override;
	virtual void Update(ck::World* world) override;
};
