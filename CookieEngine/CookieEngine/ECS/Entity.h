#pragma once

namespace cookie
{
	struct Entity
	{
		unsigned int index;
		unsigned int gen;
	public:
		Entity(unsigned int index, unsigned int generation) : index { index }, gen { generation }{}

		bool operator==(const Entity& other) const
		{
			return gen == other.gen && index == other.index;
		}
		friend class World;
	};
}