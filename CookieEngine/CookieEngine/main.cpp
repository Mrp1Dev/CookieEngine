#include "ECS/Entity.h"
#include <iostream>
#include <vector>

using namespace cookie;
int main()
{
	Entity<int, float> entity = cookie::Entity<int, float>(1, 3.0f);
	std::vector<IncompleteEntity> entities;
	entities.push_back(Entity<int, float>(1, 3.0f));
	std::cout << *std::get<0>(entities[0].QueryEntity<int>());
}