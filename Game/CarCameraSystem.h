#pragma once
#include <ECS/World.h>

class CarCameraSystem final : public ck::System
{
public:
	void FixedUpdate(ck::World* world) override;
};