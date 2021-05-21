#include "World.h"

namespace cookie
{
	inline void World::StartSystems()
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
	inline void World::UpdateSystems()
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
	inline void World::DestroySystems()
	{
		for (auto& system : this->systems)
		{
			system->Destroy(this);
		}
	}
	inline World* World::EnqueueEntityDespawn(Entity entity)
	{
		if (entity.gen == currentEntities.at(entity.index).gen)
		{
			auto f = std::bind(&World::despawnEntity, this, entity.index);
			commands.push_back(f);
		}
		return this;
	}
	inline void World::despawnEntity(unsigned int index)
	{
		despawnedEntities.push_back(index);
		currentEntities.at(index).gen++;
		for (auto& pair : ComponentsMap)
		{
			pair.second->clear(index);
		}
		queriesDirty = true;
	}

	template<class ...Systems>
	inline World::World(Systems ...systems)
	{
		(this->systems.push_back(std::make_unique<Systems>(systems)), ...);
	}

	template<class T>
	inline World* World::AddSystem(T system, bool callStart)
	{
		this->systems.push_back(std::make_unique<T>(system));
		if (callStart) systems.back()->Start(this);
		return this;
	}

	template<class T>
	inline T* World::AddResource(T res)
	{
		auto insertedResource = resources.insert_or_assign(std::type_index(typeid(T)).hash_code(), res);
		auto& first = insertedResource.first;

		return std::any_cast<T>(&first->second);
	}

	template<class T>
	inline T* World::GetResource()
	{
		auto existing = resources.find(std::type_index(typeid(T)).hash_code());
		if (existing != resources.end())
		{
			return std::any_cast<T>(&existing->second);
		}
		return nullptr;
	}

	template<class ...Components>
	inline World* World::EnqueueEntitySpawn(Components ...components)
	{
		auto f = std::bind(&World::spawnEntity<Components...>, this, components...);
		commands.push_back(f);
		return this;
	}

	template<class ...QueryTypes>
	inline Query<QueryTypes...>* World::QueryEntities()
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

	template<class ...ComponentTypes>
	inline std::optional<std::tuple<Ref<ComponentTypes>...>> World::TryGetComponents(Entity entity)
	{
		if (entity.gen < currentEntities.at(entity.index).gen)
		{
			return {};
		}
		return queryEntity<ComponentTypes...>(entity.index, getVectorPointer<ComponentTypes>()...);
	}

	template<class T>
	inline std::optional<Ref<T>> World::TryGetComponent(Entity entity)
	{
		auto component = TryGetComponents<T>(entity);
		if (component.has_value())
		{
			return std::get<0>(component.value());
		}
		return {};
	}

	template<class ...Components>
	inline void World::spawnEntity(Components ...components)
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

	template<class ComponentType>
	inline void World::addComponentVector()
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
	inline void World::assignComponent(ComponentType& component, int entityIndex)
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

	template<class ...QueryTypes>
	inline Query<QueryTypes...> World::queryEntitiesWithPointers(std::vector<std::optional<QueryTypes>>* ...vectorPointers) const
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

	template<class ...QueryTypes>
	inline std::optional<std::tuple<Ref<QueryTypes>...>> World::queryEntity(unsigned int index, std::vector<std::optional<QueryTypes>>* ...componentVectors) const
	{

		bool isCompleteQuery = (((componentVectors != nullptr) && ...) && ((componentVectors->size() > index) && ...));

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
	inline std::vector<std::optional<VectorType>>* World::getVectorPointer() const
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
	inline void World::setValueIfNullopt(std::optional<Type> opt, bool* boolToSet, bool value)
	{
		if (!opt.has_value())
		{
			*boolToSet = value;
		}
	}

	template<class Type>
	inline void World::setValueIfNullopt(Type* pointer, bool* boolToSet, bool value)
	{
		if (pointer == nullptr)
		{
			*boolToSet = value;
		}
	}
}