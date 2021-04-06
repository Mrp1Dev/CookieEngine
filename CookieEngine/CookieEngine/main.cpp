#include <optional>
#include <iostream>
#include <functional>
#include "ECS/World.h"
#include "temporary_types.h"

class PrintAllFloats : public cookie::System
{
public:
	virtual void Start(cookie::World* world) override
	{
		auto query { world->QueryEntities<float, int>() };
		query.For([](auto f, auto i)
			{
				std::cout << *f << ' ' << *i << '\n';
			});
	}
};

class SpawnFloats : public cookie::System
{
public:
	virtual void Start(cookie::World* world) override
	{
		world->EnqueueEntitySpawn(100.0f, 200);
	}
};
int main()
{
	cookie::World world {};
	world.Start(SpawnFloats {}, PrintAllFloats {});
}