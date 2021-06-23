#pragma once
#include <ECS/World.h>
#include <Constants.h>
#include <RenderingComponents.h>
#include <IO/AssetManager.h>

class SpawnLevelItemsSystem : public ck::System
{
	void SpawnPlayer(ck::World* world);
	void SpawnCity(ck::World* world);
	ck::Entity SpawnCar(ck::World* world);
public:
	virtual void Start(ck::World* world) override;
	void SpawnCamera(cookie::World* world, const cookie::Entity& car);
	void SetUpDirLight(ck::World* world);
};