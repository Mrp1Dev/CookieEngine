#pragma once
#include "Ref.h"
#include <vector>
#include <functional>

namespace cookie
{
	template<class... QueryTypes>
	class Query
	{
		std::vector<std::tuple<cookie::Ref<QueryTypes>...>> query;
	public:
		Query(std::vector<std::tuple<cookie::Ref<QueryTypes>...>>& query)
			: query { std::move(query) }
		{
		};

		void For(std::function<void(cookie::Ref<QueryTypes>...)> function)
		{
			for (auto& tuple : query)
			{
				function(std::get<cookie::Ref<QueryTypes>>(tuple)...);
			}
		}
	};
}