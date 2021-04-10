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
#include <map>

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
			unsigned int commandsLength = commands.size();
			for (int i = 0; i < commandsLength; i++)
			{
				commands.front()();
				commands.pop_front();
			}
		}

		void UpdateSystems()
		{
			unsigned int commandsLength = commands.size();
			for (int i = 0; i < commandsLength; i++)
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
			return queryEntitiesWithPointers(getVectorPointer<QueryTypes>()...);
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
							std::vector<std::optional<ComponentType>>(EntityCount + 1u)
							)
					)
				);
			};
		}

		template<class ComponentType>
		void assignComponent(ComponentType& component, int entityIndex)
		{
			auto componentVector =
				std::any_cast<std::vector<std::optional<ComponentType>>>(
					&(ComponentsMap.find(typeid(ComponentType).hash_code())->second)
					);
			if (entityIndex >= componentVector->size())
			{
				componentVector->resize(EntityCount + 1);
			}
			componentVector->at(entityIndex) = std::move(component);
		}

		template<class... QueryTypes>
		Query<QueryTypes...> queryEntitiesWithPointers(std::vector<std::optional<QueryTypes>>*... vectorPointers)
		{
			std::vector<std::tuple<Ref<QueryTypes>...>> result {};
			bool isValidQuery = ((vectorPointers != nullptr) && ...);
			if (!isValidQuery) return Query(result);
			result.reserve(EntityCount);
			for (unsigned int i = 0; i < EntityCount; i++)
			{
				auto query { queryEntity(i, vectorPointers...) };
				if (query.has_value())
				{
					result.push_back(query.value());
				}
			}
			return Query(result);
		}

		template<class... QueryTypes>
		std::optional<std::tuple<Ref<QueryTypes>...>> queryEntity(unsigned int index, std::vector<std::optional<QueryTypes>>*... componentVectors)
		{
			bool isCompleteQuery = ((componentVectors->size() > index ) && ...);
			if (isCompleteQuery)
			{
				isCompleteQuery = (componentVectors->at(index).has_value() && ...);
				if (isCompleteQuery)
				{
					return std::tuple<Ref<QueryTypes>...>{Ref<QueryTypes>(componentVectors, index)...};
				}
			}
			return {};
		}

		//template<class QueryType>
		//std::optional<Ref<QueryType>> queryComponent(unsigned int index, std::vector<std::optional<QueryType>>* componentVector)
		//{
		//	if (index >= componentVector->size())
		//	{
		//		return {};
		//	}

		//	if (componentVector->at(index).has_value())
		//	{
		//		return Ref<QueryType>(componentVector, index);
		//	}
		//	return {};
		//}

		template<class VectorType>
		std::vector<std::optional<VectorType>>* getVectorPointer()
		{
			auto pairfromMap = ComponentsMap.find(typeid(VectorType).hash_code());
			if (pairfromMap != ComponentsMap.end())
			{
				return std::any_cast<std::vector<std::optional<VectorType>>>(
					&pairfromMap->second);
			}
			return nullptr;
		}

		template<class Type>
		void setValueIfNullopt(std::optional<Type> opt, bool* boolToSet, bool value)
		{
			if (!opt.has_value())
			{
				*boolToSet = value;
			}
		}

		template<class Type>
		void setValueIfNullopt(Type* pointer, bool* boolToSet, bool value)
		{
			if (pointer == nullptr)
			{
				*boolToSet = value;
			}
		}
	};


}