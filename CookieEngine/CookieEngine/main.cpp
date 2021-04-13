#include <optional>
#include <iostream>
#include <functional>
#include "ECS/World.h"
#include "temporary_types.h"
#include <chrono>

struct IStoreEntity
{
	cookie::Entity entity;
};

class QueryLots : public cookie::System
{
public:
	virtual void Update(cookie::World* world) override
	{
		auto query = world->QueryEntities<int>();
		query->For([&world](cookie::Entity entity, auto i)
			{
				*i += 2;
				if (*i == 29)
				{
					world->EnqueueEntitySpawn(IStoreEntity { entity });
					std::cout << "shit spawned" << '\n';
				}
			});
		auto storeQuery = world->QueryEntities<IStoreEntity>();
		std::cout << storeQuery->query.size();
		storeQuery->For([&world](auto store)
			{
				auto i = std::get<0>(world->TryGetComponents<int>(store->entity).value());
				std::cout << "bleh" << '\n';
				std::cout << *i << '\n';
				*i *= 2;
			});
	}
};

class SpawnEntities : public cookie::System
{
public:
	virtual void Start(cookie::World* world) override
	{
		for (int i = 0; i < 1000000; i++)
		{
			world->EnqueueEntitySpawn(i + 1);
		}
	}
};
int main()
{
	cookie::World world {
	SpawnEntities {}, QueryLots {}
	};

	world.StartSystems();
	auto t1 = std::chrono::steady_clock::now();
	world.UpdateSystems();
	auto t2 = std::chrono::steady_clock::now();
	auto d = t2 - t1;
	std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(d).count() << "ms\n";

	//SPAWNING TAKES: About 175ms

	auto t3 = std::chrono::steady_clock::now();
	for (int i = 0; i < 1000; i++)
	{
		world.UpdateSystems();
	}
	auto t4 = std::chrono::steady_clock::now();
	auto d1 = t4 - t3;
	std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(d1).count() << "ms\n";

	//QUERYING TAKES: About 16ms
}