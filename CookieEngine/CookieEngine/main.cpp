#include <optional>
#include <iostream>
#include <functional>
#include "ECS/World.h"
#include "temporary_types.h"
template<class... QueryTypes>
class Query
{
	std::vector<std::tuple<cookie::Ref<QueryTypes>...>> query;
public:
	Query(std::vector<std::tuple<cookie::Ref<QueryTypes>...>> query)
		: query { query }
	{
	};

	void For(std::function<void(cookie::Ref<QueryTypes>...)> function)
	{
		for (auto& tuple : query)
		{
			function(std::get<cookie::Ref<QueryTypes>>(tuple)...);
		}
	}
};
int main()
{
	cookie::World world {};
	world.SpawnEntity(Position { 3.0f }, Rotation { 54.0f }, 3265.0f);
	world.SpawnEntity(Position { 9.0f });
	world.SpawnEntity(Rotation { 599.0f });
	world.SpawnEntity(Rotation { 56.0f }, 128.0f);
	//auto query { world.QueryEntities<Rotation, float>() };
	world.ForEachEntity<Rotation, float>([](auto rot, auto n)
		{
			std::cout << "Rot: " << rot->x << '\n';
			std::cout << "n: " << *n << '\n';
			rot->x *= 2;
		});
	world.ForEachEntity<Rotation, float>([](auto rot, auto n)
		{
			std::cout << "Rot: " << rot->x << '\n';
			std::cout << "n: " << *n << '\n';
			rot->x *= 2;
		});
}