#pragma once
#include <ECS/World.h>
#include <Constants.h>
#include <RenderingComponents.h>
#include <IO/AssetManager.h>

class SpawnLevelItemsSystem : public ck::System
{
	void SpawnPlayer(ck::World* world);
	void SpawnCity(cookie::World* world);
public:
	virtual void Start(ck::World* world) override;
	void SetUpDirLight(cookie::World* world);
	void SpawnCar(cookie::World* world);
};