#include <optional>
#include <iostream>
#include <functional>
#include "ECS/World.h"
#include "temporary_types.h"
#include <chrono>
class QueryLots : public cookie::System
{
public:
	virtual void Update(cookie::World* world) override
	{
		auto query { world->QueryEntities<int>() };
		query.For([](auto f)
			{
				*f += 2;
			});
	}
};

class SpawnEntities : public cookie::System
{
public:
	virtual void Start(cookie::World* world) override
	{
		world->EnqueueEntitySpawn(100.0f, 200, 399L, 1.0, 159u);
		for (int i = 0; i < 1000000; i++)
		{
			world->EnqueueEntitySpawn(i);
		}
	}
};
int main()
{
	cookie::World world {
	SpawnEntities {}, QueryLots {}
	};

	auto t1 = std::chrono::steady_clock::now();
	world.StartSystems();
	auto t2 = std::chrono::steady_clock::now();
	auto d = t2 - t1;
	std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(d).count() << '\n';

	//SPAWNING TAKES: About 4400ms

	auto t3 = std::chrono::steady_clock::now();
	//world.StartSystems();
	for (int i = 0; i < 1; i++)
	{
		world.UpdateSystems();
	}
	auto t4 = std::chrono::steady_clock::now();
	auto d1 = t4 - t3;
	std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(d1).count();

	while (true)
	{
	}
	//QUERYING TAKES: About 3000ms
}