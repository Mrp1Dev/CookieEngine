#pragma once
#include <ECS/World.h>

class CarCameraSystem final : public ck::System
{
public:
	void Update(ck::World* world) override;
};