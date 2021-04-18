#pragma once
#include <unordered_map>
#include <typeinfo>
#include <memory>
#include <iostream>
#include <deque>
#include "ComponentArray.h"
#include "Query.h"
#include "System.h"
#include <map>
#include "Entity.h"

namespace cookie
{
	class World
	{
		template<class... Types>
		class TypePack
		{
		};
		std::vector<std::unique_ptr<System>> systems;
		std::deque<std::function<void()>> commands;
		std::deque<unsigned int> despawnedEntities;
		std::unordered_map<size_t, std::unique_ptr<QueryBase>> cachedQueries;
		std::vector<Entity> currentEntities;
		bool queriesDirty { true };
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
			queriesDirty = false;
		}

		void DestroySystems()
		{
			for (auto& system : this->systems)
			{
				system->Destroy(this);
			}
		}

		template<class T>
		World* AddSystem(T system, bool callStart = true)
		{
			this->systems.push_back(std::make_unique<System>(system));
			if (callStart) systems.back->Start();
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
			if (entity.gen == currentEntities.at(entity.index).gen)
			{
				auto f = std::bind(&World::despawnEntity, this, entity.index);
				commands.push_back(f);
			}
			return this;
		}


		template<class... QueryTypes>
		Query<QueryTypes...>* QueryEntities()
		{
			size_t typeId = typeid(TypePack<QueryTypes...>{}).hash_code();
			auto cacheFind = cachedQueries.find(typeId);
			if (cacheFind != cachedQueries.end() && !queriesDirty)
			{
				return static_cast<Query<QueryTypes...>*>(cacheFind->second.get());
			}
			return static_cast<Query<QueryTypes...>*>(cachedQueries.insert_or_assign(
				typeId,
				std::make_unique<Query<QueryTypes...>>(
					queryEntitiesWithPointers(getVectorPointer<QueryTypes>()...)
					)
			).first->second.get());

		}

		template<class... ComponentTypes>
		std::optional<std::tuple<Ref<ComponentTypes>...>> TryGetComponents(Entity entity)
		{
			if (entity.gen < currentEntities.at(entity.index).gen)
			{
				return {};
			}
			return queryEntity<ComponentTypes...>(entity.index, getVectorPointer<ComponentTypes>()...);
		}

		template<class T>
		std::optional<Ref<T>> TryGetComponent(Entity entity)
		{
			auto component = TryGetComponents<T>(entity);
			if (component.has_value())
			{
				return std::get<0>(component.value());
			}
			return {};
		}

	private:

		template<class... Components>
		void spawnEntity(Components... components)
		{
			(addComponentVector<Components>(), ...);
			if (despawnedEntities.size() > 0)
			{
				(assignComponent<Components>(components, despawnedEntities.front()), ...);
				despawnedEntities.pop_front();
			}
			else
			{
				(assignComponent<Components>(components, EntityCount), ...);
				currentEntities.push_back(Entity(EntityCount, 0));
			}
			EntityCount++;
			queriesDirty = true;
		}

		void despawnEntity(unsigned int index)
		{
			despawnedEntities.push_back(index);
			currentEntities.at(index).gen++;
			for (auto& pair : ComponentsMap)
			{
				pair.second->clear(index);
			}
			queriesDirty = true;
		}

		template<class ComponentType>
		void addComponentVector()
		{
			if (ComponentsMap.find(typeid(ComponentType).hash_code()) == ComponentsMap.end())
			{
				ComponentsMap.insert(
					std::pair(
						typeid(ComponentType).hash_code(),
						std::make_unique<ComponentArray<ComponentType>>(
							std::vector<std::optional<ComponentType>>(EntityCount + 1u))
					)
				);
			};
		}

		template<class ComponentType>
		void assignComponent(ComponentType& component, int entityIndex)
		{
			auto componentVector =
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
		Query<QueryTypes...> queryEntitiesWithPointers(std::vector<std::optional<QueryTypes>>*... vectorPointers) const
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
				{
					result.push_back(query.value());
					entities.push_back(currentEntities.at(i));
				}
			}
			return Query(result, entities);
		}

		template<class... QueryTypes>
		std::optional<std::tuple<Ref<QueryTypes>...>> queryEntity(unsigned int index, std::vector<std::optional<QueryTypes>>*... componentVectors) const
		{
			bool isCompleteQuery = (((componentVectors->size() > index) && ...) && ((componentVectors != nullptr) && ...));

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

		template<class VectorType>
		std::vector<std::optional<VectorType>>* getVectorPointer() const
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