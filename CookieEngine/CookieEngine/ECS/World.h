#pragma once
#include <vector>
#include <unordered_map>
#include <typeinfo>
#include <memory>
#include <any>
#include <optional>
#include <iostream>
#include <deque>
#include "Query.h"
#include "System.h"
#include "Entity.h"

namespace cookie
{

	class World
	{
		std::vector<std::unique_ptr<System>> systems;
		std::deque<std::function<void()>> commands;
		std::vector<Entity> entities;
	public:
		unsigned int EntityCount { 0 };
		std::unordered_map<size_t, std::any> ComponentsMap;
		bool GameRunning { true };

		template<class... Systems>
		World(Systems... systems)
		{
			(this->systems.push_back(std::make_unique<Systems>(systems)), ...);
		}

		void StartSystems()
		{
			for (auto& system : this->systems)
			{
				system->Start(this);
			}
			for (int i = 0; i < commands.size(); i++)
			{
				commands.front()();
				commands.pop_front();
			}
		}

		void UpdateSystems()
		{
			for (int i = 0; i < commands.size(); i++)
			{
				commands.front()();
				commands.pop_front();
			}
			for (auto& system : this->systems)
			{
				system->Update(this);
			}
		}

		void DestroySystems()
		{
			for (auto& system : this->systems)
			{
				system->Destroy(this);
			}
		}

		template<class... Components>
		World* EnqueueEntitySpawn(Components... components)
		{
			auto f = std::bind(&World::spawnEntity<Components...>, this, components...);
			commands.push_back(f);
			return this;
		}

		template<class... QueryTypes>
		Query<QueryTypes...> QueryEntities()
		{
			std::vector<std::tuple<Ref<QueryTypes>...>> result {};
			for (auto& entity : entities)
			{
				auto query { queryEntity<QueryTypes...>(entity) };
				if (query.has_value())
				{
					result.push_back(query.value());
				}
			}
			return Query(result);
		}
	private:

		template<class... Components>
		void spawnEntity(Components... components)
		{
			Entity spawnedEntity {};
			(addComponentVector<Components>(), ...);
			(assignComponent<Components>(components, &spawnedEntity), ...);
			entities.push_back(spawnedEntity);
		}

		template<class ComponentType>
		void addComponentVector()
		{
			if (ComponentsMap.find(typeid(ComponentType).hash_code()) == ComponentsMap.end())
			{
				ComponentsMap.insert(
					std::pair(
						typeid(ComponentType).hash_code(),
						static_cast<std::any>(
							std::vector<ComponentType>()
							)
					)
				);
			};
		}

		template<class ComponentType>
		void assignComponent(ComponentType component, Entity* entity)
		{
			size_t typeId = typeid(ComponentType).hash_code();
			auto componentVector =
				std::any_cast<std::vector<ComponentType>>(
					&(ComponentsMap[typeid(ComponentType).hash_code()])
					);
			componentVector->push_back(component);
			entity->components.insert( move(
				std::pair {
					typeId,
					std::make_shared<Ref<ComponentType>>(componentVector,
					componentVector->size() - 1)
				})
			);
		}

		template<class... QueryTypes>
		std::optional<std::tuple<Ref<QueryTypes>...>> queryEntity(Entity& entity)
		{
			bool isIncompleteQuery { false };
			auto queryTuple = std::tuple<std::optional<Ref<QueryTypes>>...> { queryComponent<QueryTypes>(entity)... };

			std::apply([this, &isIncompleteQuery](auto&... pointers) mutable
				{
					(setValueIfNullopt<Ref<QueryTypes>>(pointers, &isIncompleteQuery, true), ...);
				}, queryTuple
			);

			if (!isIncompleteQuery)
			{
				std::tuple<Ref<QueryTypes>...> resultTuple
				{
					std::get<std::optional<Ref<QueryTypes>>>(queryTuple).value()...
				};
				return resultTuple;
			}
			return {};
		}

		template<class QueryType>
		std::optional<Ref<QueryType>> queryComponent(Entity& entity)
		{
			size_t typeId = typeid(QueryType).hash_code();
			if (entity.components.find(typeId) != entity.components.end())
			{
				return *static_cast<Ref<QueryType>*>(entity.components[typeId].get());
			}
			return {};
		}

		template<class Type>
		void setValueIfNullopt(std::optional<Type> opt, bool* boolToSet, bool value)
		{
			if (!opt.has_value())
			{
				*boolToSet = value;
			}
		}
	};


}