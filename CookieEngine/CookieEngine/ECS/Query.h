#pragma once
#include "Ref.h"
#include "Entity.h"
#include <vector>
#include <functional>

namespace cookie
{
	template<class... QueryTypes>
	class Query
	{
		std::vector<std::tuple<cookie::Ref<QueryTypes>...>> query;
		std::vector<Entity> entities;
	public:
		Query(std::vector<std::tuple<cookie::Ref<QueryTypes>...>>& query, std::vector<Entity>& entities)
			: query { std::move(query) }, entities { std::move(entities) }
		{
		};

		void For(std::function<void(cookie::Ref<QueryTypes>...)> function)
		{
			for (auto& tuple : query)
			{
				function(std::get<cookie::Ref<QueryTypes>>(tuple)...);
			}
		}

		void For(std::function<void(Entity, cookie::Ref<QueryTypes>...)> function)
		{
			for (unsigned int i = 0; i < query.size(); i++)
			{
				function(entities.at(i), std::get<cookie::Ref<QueryTypes>>(query.at(i))...);
			}
		}
	};
}