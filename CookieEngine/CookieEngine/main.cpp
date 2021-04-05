#include <optional>
#include "World.h"
#include <iostream>

struct Blegh
{
	float meh {};
};

int main()
{
	cookie::World world {};
	world.SpawnEntity(cookie::Position { 1 }, cookie::Rotation { 64.0f }, Blegh { 5343.0f });
	world.SpawnEntity(cookie::Position { 3 }, cookie::Rotation { 32.0f });
	auto query { world.QueryEntities<cookie::Position, Blegh>() };

	for (auto& tuple : query)
	{
		auto pos = std::get<0>(tuple);
		std::cout << pos->x << '\n';
		pos->x = 6999;
		auto blegh = std::get<1>(tuple);
		std::cout << blegh->meh << '\n';
	}

	for (auto& tuple : query)
	{
		auto pos = std::get<0>(tuple);
		std::cout << pos->x << '\n';
		auto blegh = std::get<1>(tuple);
		std::cout << blegh->meh << '\n';
	}

}