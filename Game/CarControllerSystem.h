#pragma once
#include <ECS/World.h>

class CarControllerSystem final : public ck::System
{
public:
	void FixedUpdate(ck::World* world) override;
};