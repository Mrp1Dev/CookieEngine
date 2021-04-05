#include <optional>
#include "World.h"
#include <iostream>

int main()
{
	cookie::World world {};
	world.SpawnEntity(cookie::Position {1}, cookie::temp_rotation {});
	world.SpawnEntity(cookie::Position {3});
	auto query { world.QueryEntities<cookie::Position>() };
	float currX = 1.0f;
	/*for (auto& tuple : query)
	{
		auto pos = std::get<0>(tuple);
		pos->x += currX;
		currX += pos->x;
	}*/

	for (auto& tuple : query)
	{
		auto pos = std::get<0>(tuple);
		std::cout << pos->x;
	}
}