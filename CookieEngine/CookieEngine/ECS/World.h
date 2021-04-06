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

namespace cookie
{
	
	class World
	{
		std::vector<std::unique_ptr<System>> systems;
		std::deque<std::function<void()>> commands;
	public:
		unsigned int EntityCount { 0 };
		std::unordered_map<size_t, std::any> ComponentsMap;
		bool GameRunning { true };

		template<class... Systems>
		void Start(Systems... systems)
		{
			(this->systems.push_back(std::make_unique<Systems>(systems)), ...);

			for (auto& system : this->systems)
			{
				system->Start(this);
				for (int i = 0; i < commands.size(); i++)
				{
					commands.front()();
					commands.pop_front();
				}
			}

			while (GameRunning)
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
			for (int i = 0; i < EntityCount; i++)
			{
				auto query { queryEntity<QueryTypes...>(i) };
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
			(addComponentVector<Components>(), ...);
			(assignComponent<Components>(components, EntityCount), ...);
			EntityCount++;
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
							std::vector<std::optional<ComponentType>>(EntityCount + 1)
							)
					)
				);
			};
		}

		template<class ComponentType>
		void assignComponent(ComponentType component, int entityIndex)
		{
			auto componentVector =
				std::any_cast<std::vector<std::optional<ComponentType>>>(
					&(ComponentsMap[typeid(ComponentType).hash_code()])
					);
			if (entityIndex >= componentVector->size())
			{
				componentVector->resize(EntityCount + 1);
			}
			componentVector->at(entityIndex) = component;
		}

		template<class... QueryTypes>
		std::optional<std::tuple<Ref<QueryTypes>...>> queryEntity(unsigned int index)
		{
			bool isIncompleteQuery { false };
			auto queryTuple = std::tuple<std::optional<Ref<QueryTypes>>...> { queryComponent<QueryTypes>(index)... };

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
		std::optional<Ref<QueryType>> queryComponent(unsigned int index)
		{
			auto componentVector =
				std::any_cast<std::vector<std::optional<QueryType>>>(
					&ComponentsMap[typeid(QueryType).hash_code()]);
			if (componentVector == nullptr) return {};
			if (index >= componentVector->size())
			{
				componentVector->resize(EntityCount);
			}

			if (componentVector->at(index).has_value())
			{
				return Ref<QueryType>(componentVector, index);
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