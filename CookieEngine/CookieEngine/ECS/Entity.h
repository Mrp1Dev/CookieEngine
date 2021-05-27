#pragma once
#include <Usings.h>
namespace cookie
{
	struct Entity
	{
		u32 index;
		u32 gen;
	public:
		Entity(u32 index, u32 generation) : index { index }, gen { generation }{}

		bool operator==(const Entity& other) const
		{
			return gen == other.gen && index == other.index;
		}
		friend class World;
	};
}