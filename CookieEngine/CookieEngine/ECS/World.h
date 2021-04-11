#pragma once
#include <unordered_map>
#include <typeinfo>
#include <memory>
#include <iostream>
#include <deque>
#include "ComponentArray.h"
#include "Query.h"
#include "System.h"
<<<<<<< HEAD
#include "Entity.h"

=======
#include <map>
#include "Entity.h"
>>>>>>> origin/PreRefactorizationBranch
namespace cookie
{

	class World
	{
		std::vector<std::unique_ptr<System>> systems;
		std::deque<std::function<void()>> commands;
<<<<<<< HEAD
		std::vector<Entity> entities;
=======
		std::deque<unsigned int> despawnedEntities;

>>>>>>> origin/PreRefactorizationBranch
	public:
		unsigned int EntityCount { 0 };
		std::unordered_map<size_t, std::unique_ptr<BaseComponentArray>> ComponentsMap;
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

		World* EnqueueEntityDespawn(Entity entity)
		{
			auto f = std::bind(&World::despawnEntity, this, entity.index);
			commands.push_back(f);
			return this;
		}


		template<class... QueryTypes>
		Query<QueryTypes...> QueryEntities()
		{
<<<<<<< HEAD
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
=======
			return queryEntitiesWithPointers(getVectorPointer<QueryTypes>()...);
>>>>>>> origin/PreRefactorizationBranch
		}

	private:

		template<class... Components>
		void spawnEntity(Components... components)
		{
			Entity spawnedEntity {};
			(addComponentVector<Components>(), ...);
<<<<<<< HEAD
			(assignComponent<Components>(components, &spawnedEntity), ...);
			entities.push_back(spawnedEntity);
=======
			if (despawnedEntities.size() > 0)
			{
				(assignComponent<Components>(components, despawnedEntities.front()), ...);
				despawnedEntities.pop_front();
			}
			else
			{
				(assignComponent<Components>(components, EntityCount), ...);
			}
			EntityCount++;
>>>>>>> origin/PreRefactorizationBranch
		}

		void despawnEntity(unsigned int index)
		{
			despawnedEntities.push_back(index);
			for (auto& pair : ComponentsMap)
			{
				pair.second->clear(index);
			}
		}

		template<class ComponentType>
		void addComponentVector()
		{
			if (ComponentsMap.find(typeid(ComponentType).hash_code()) == ComponentsMap.end())
			{
				ComponentsMap.insert(
					std::pair(
						typeid(ComponentType).hash_code(),
<<<<<<< HEAD
						static_cast<std::any>(
							std::vector<ComponentType>()
							)
=======
						std::make_unique<ComponentArray<ComponentType>>(
							std::vector<std::optional<ComponentType>>(EntityCount + 1u))
>>>>>>> origin/PreRefactorizationBranch
					)
				);
			};
		}

		template<class ComponentType>
<<<<<<< HEAD
		void assignComponent(ComponentType component, Entity* entity)
=======
		void assignComponent(ComponentType& component, int entityIndex)
>>>>>>> origin/PreRefactorizationBranch
		{
			size_t typeId = typeid(ComponentType).hash_code();
			auto componentVector =
<<<<<<< HEAD
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
=======
				static_cast<ComponentArray<ComponentType>*>(
					ComponentsMap.find(typeid(ComponentType).hash_code())->second.get()
					);
			if (entityIndex >= componentVector->Components.size())
			{
				componentVector->Components.resize(EntityCount + 1);
			}
			componentVector->Components.at(entityIndex) = std::move(component);
		}

		template<class... QueryTypes>
		Query<QueryTypes...> queryEntitiesWithPointers(std::vector<std::optional<QueryTypes>>*... vectorPointers)
		{
			std::vector<std::tuple<Ref<QueryTypes>...>> result {};
			std::vector<Entity> entities {};
			bool isValidQuery = ((vectorPointers != nullptr) && ...);
			if (!isValidQuery) return Query(result, entities);
			result.reserve(EntityCount);
			entities.reserve(EntityCount);
			for (unsigned int i = 0; i < EntityCount; i++)
			{
				auto query { queryEntity(i, vectorPointers...) };
				if (query.has_value())
>>>>>>> origin/PreRefactorizationBranch
				{
					result.push_back(query.value());
					entities.push_back(Entity { i });
				}
			}
			return Query(result, entities);
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

<<<<<<< HEAD
		template<class QueryType>
		std::optional<Ref<QueryType>> queryComponent(Entity& entity)
		{
			size_t typeId = typeid(QueryType).hash_code();
			if (entity.components.find(typeId) != entity.components.end())
			{
				return *static_cast<Ref<QueryType>*>(entity.components[typeId].get());
=======
		template<class VectorType>
		std::vector<std::optional<VectorType>>* getVectorPointer()
		{
			auto pairfromMap = ComponentsMap.find(typeid(VectorType).hash_code());
			if (pairfromMap != ComponentsMap.end())
			{
				return &static_cast<ComponentArray<VectorType>*>(
					pairfromMap->second.get())->Components;
			}
			return nullptr;
		}

		template<class Type>
		void setValueIfNullopt(std::optional<Type> opt, bool* boolToSet, bool value)
		{
			if (!opt.has_value())
			{
				*boolToSet = value;
>>>>>>> origin/PreRefactorizationBranch
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