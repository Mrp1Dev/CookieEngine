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
#include <any>
#include <typeindex>

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
		std::unordered_map<size_t, std::any> resources;

		bool queriesDirty { true };
	public:
		unsigned int EntityCount { 0 };
		std::unordered_map<size_t, std::unique_ptr<BaseComponentArray>> ComponentsMap;
		bool GameRunning { true };

		template<class... Systems>
		World(Systems... systems);

		void StartSystems();

		void UpdateSystems();

		void DestroySystems();

		template<class T>
		World* AddSystem(T system, bool callStart = true);

		template<class T>
		T* AddResource(T res);

		template<class T>
		T* GetResource();

		template<class... Components>
		World* EnqueueEntitySpawn(Components... components);

		World* EnqueueEntityDespawn(Entity entity);


		template<class... QueryTypes>
		Query<QueryTypes...>* QueryEntities();

		template<class... ComponentTypes>
		std::optional<std::tuple<Ref<ComponentTypes>...>> TryGetComponents(Entity entity);

		template<class T>
		std::optional<Ref<T>> TryGetComponent(Entity entity);

	private:

		template<class... Components>
		void spawnEntity(Components... components);

		void despawnEntity(unsigned int index);

		template<class ComponentType>
		void addComponentVector();

		template<class ComponentType>
		void assignComponent(ComponentType& component, int entityIndex);

		template<class... QueryTypes>
		Query<QueryTypes...> queryEntitiesWithPointers(std::vector<std::optional<QueryTypes>>*... vectorPointers) const;

		template<class... QueryTypes>
		std::optional<std::tuple<Ref<QueryTypes>...>> queryEntity(unsigned int index, std::vector<std::optional<QueryTypes>>*... componentVectors) const;

		template<class VectorType>
		std::vector<std::optional<VectorType>>* getVectorPointer() const;

		template<class Type>
		void setValueIfNullopt(std::optional<Type> opt, bool* boolToSet, bool value);

		template<class Type>
		void setValueIfNullopt(Type* pointer, bool* boolToSet, bool value);
	};
}
namespace ck = cookie;