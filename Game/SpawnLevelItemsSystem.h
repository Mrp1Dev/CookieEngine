#pragma once
#include <ECS/World.h>
#include <Constants.h>
#include <RenderingComponents.h>
#include <IO/AssetManager.h>
namespace ck = cookie;

class SpawnLevelItemsSystem : public ck::System
{
public:
	virtual void Start(ck::World* world) override;
};