#pragma once
#include "../CookieEngine/ECS/World.h"
#include "../CookieEngine/IO/AssetManager.h"
#include "../CookieEngine//Rendering/TransformData.h"
#include "../CookieEngine//Rendering/BaseColorData.h"
#include "../CookieEngine/CookieEngine/Constants/DefaultShaders .h"
namespace ck = cookie;

class SpawnBagsSystem : public ck::System
{
public:
	virtual void Start(ck::World* world) override;
};