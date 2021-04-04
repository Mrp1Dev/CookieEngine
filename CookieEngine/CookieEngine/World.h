#pragma once
#include <vector>
#include <unordered_map>
#include <typeinfo>
#include "ECS/Component.h"
#include <memory>
#include <any>
#include <optional>

namespace cookie
{
	class Position : public Component
	{
	};
	class temp_rotation : public Component
	{
	};

	class World
	{
	public:
		unsigned int EntityCount { 0 };
		std::unordered_map<size_t, std::any> ComponentsMap;

		template<class... Components>
		World* SpawnEntity(Components... components)
		{
			(fillMap<Components>(), ...);
			(assignComponent<Components>(components, EntityCount), ...);
			EntityCount++;
			return this;
		}
	private:
		template<class ComponentType>
		void fillMap()
		{
			if (ComponentsMap.find(typeid(ComponentType).hash_code()) == ComponentsMap.end())
			{
				ComponentsMap.insert(
					std::make_pair(
						typeid(ComponentType).hash_code(),
						static_cast<std::any>(
							std::vector<std::optional<ComponentType>>(
								EntityCount + 1, std::optional<ComponentType>()
								)
							)
					)
				);
			};
		}

		template<class ComponentType>
		void assignComponent(ComponentType component, int index)
		{
			std::any_cast<std::vector<std::optional<ComponentType>>>(
				ComponentsMap[typeid(ComponentType).hash_code()]
				).at(index) = component;
		}
	};


}