#pragma once
#include <vector>
#include <unordered_map>
#include <typeinfo>
#include "ECS/Component.h"
#include <memory>
#include <any>
#include <optional>
#include <iostream>

namespace cookie
{
	class Position : public Component
	{
	public:
		float x {};
		Position(float bleh) : x { bleh }
		{
		};
	};
	class Rotation : public Component
	{
	public:
		float x {};
		Rotation(float bleh) : x { bleh }
		{
		};
	};
	template<class T>
	class Ref
	{
		std::vector<std::optional<T>>* vector;
		unsigned long int index;
	public:
		Ref(std::vector<std::optional<T>>* vector, unsigned long int index)
			: vector { vector }, index { index }{};
		T& operator*()
		{
			return vector->at(index).value();
		}

		T* operator->()
		{
			return &vector->at(index).value();
		}
	};

	class World
	{

	public:
		unsigned int EntityCount { 0 };
		std::unordered_map<size_t, std::any> ComponentsMap;

		template<class... Components>
		World* SpawnEntity(Components... components)
		{
			(addComponentVector<Components>(), ...);
			(assignComponent<Components>(components, EntityCount), ...);
			EntityCount++;
			return this;
		}

		template<class... QueryTypes>
		std::vector<std::tuple<Ref<QueryTypes>...>> QueryEntities()
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
			return result;
		}
	private:

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