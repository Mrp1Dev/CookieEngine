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
		auto query = world->QueryEntities<int>();
			query.For([](auto i)
				{
					*i += 2;
				});
		
	}
};

class SpawnEntities : public cookie::System
{
public:
	virtual void Start(cookie::World* world) override
	{
		for (int i = 9; i >= 0; i--)
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

	auto t1 = std::chrono::steady_clock::now();
	world.StartSystems();
	auto t2 = std::chrono::steady_clock::now();
	auto d = t2 - t1;
<<<<<<< HEAD
	std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(d).count() << '\n';
=======
	std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(d).count() << "ms\n";
>>>>>>> origin/PreRefactorizationBranch

	//SPAWNING TAKES: About 175ms

	auto t3 = std::chrono::steady_clock::now();
	for (int i = 0; i < 2; i++)
	{
		world.UpdateSystems();
	}
	auto t4 = std::chrono::steady_clock::now();
	auto d1 = t4 - t3;
	std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(d1).count() << "ms\n";

<<<<<<< HEAD
	while (true)
	{
	}
	//QUERYING TAKES: About 3000ms
=======
	//QUERYING TAKES: About 70ms
>>>>>>> origin/PreRefactorizationBranch
}