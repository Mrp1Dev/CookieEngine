#include <iostream>
#include <functional>
#include "ECS/World.h"

struct IStoreEntity
{
	cookie::Entity entity;
};

class QueryLots : public cookie::System
{
public:
	virtual void Update(cookie::World* world) override
	{
		auto storeQuery = world->QueryEntities<IStoreEntity>();
		storeQuery->Foreach([&world](auto& store)
			{
				auto i = world->TryGetComponent<int>(store.entity).value();
				std::cout << *i << '\n';
			});

		auto query = world->QueryEntities<int>();
			query->EntityForeach([&world](cookie::Entity entity, auto& i)
				{
					if (i == 2)
					{
						world->EnqueueEntitySpawn(IStoreEntity { entity });
						std::cout << "shit spawned" << '\n';
					}
					i += 1;
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
	world.UpdateSystems();
	world.UpdateSystems();
}