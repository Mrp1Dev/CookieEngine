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
	class temp_rotation : public Component
	{
	public:
		float x {};
		temp_rotation(float bleh) : x { bleh }
		{
		};
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
		std::vector<std::tuple<QueryTypes*...>> QueryEntities()
		{
			std::vector<std::tuple<QueryTypes*...>> result {};
			for (int i = 0; i < EntityCount; i++)
			{
				auto query { queryEntity<QueryTypes...>(i) };
				if (query.has_value())
				{
					result.push_back(query.value());
					query.reset();
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
		std::optional<std::tuple<QueryTypes*...>> queryEntity(unsigned int index)
		{
			bool isIncompleteQuery { false };
			auto resultTuple = std::tuple<QueryTypes*...> { queryComponent<QueryTypes>(index)... };

			std::apply([this, &isIncompleteQuery](auto&... pointers) mutable
				{
					(setValueIfNullptr<QueryTypes>(pointers, &isIncompleteQuery, true), ...); 
				}, resultTuple
			);

			if (!isIncompleteQuery)
			{
				return resultTuple;
			}
			return {};
		}

		template<class QueryType>
		QueryType* queryComponent(unsigned int index)
		{
			auto componentVector =
				std::any_cast<std::vector<std::optional<QueryType>>>(
					&ComponentsMap[typeid(QueryType).hash_code()]);
			if (componentVector == nullptr) return nullptr;
			if (index >= componentVector->size())
			{
				componentVector->resize(EntityCount);
			}

			if (componentVector->at(index).has_value())
			{
				return &componentVector->at(index).value();
			}
			return nullptr;
		}

		template<class Type>
		void setValueIfNullptr(Type* pointer, bool* boolToSet, bool value)
		{
			if (pointer == nullptr)
			{
				*boolToSet = value;
			}
		}
	};


}