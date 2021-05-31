#include "World.h"
#include <usings.h>
namespace cookie
{
	void World::StartSystems()
	{
		CallCommands();
		for (auto& system : this->systems)
		{
			system->Start(this);
		}
		CallCommands();
	}

	void World::UpdateSystems()
	{
		CallCommands();
		for (auto& system : this->systems)
		{
			system->Update(this);
		}
		CallCommands();
		queriesDirty = false;
	}

	void World::FixedUpdateSystems()
	{
		CallCommands();
		for (auto& system : this->systems)
		{
			system->FixedUpdate(this);
		}
		CallCommands();
	}

	void World::DestroySystems()
	{
		CallCommands();
		for (auto& system : this->systems)
		{
			system->Destroy(this);
		}
	}

	World* World::EnqueueEntityDespawn(Entity entity)
	{
		if (entity.gen == currentEntities.at(entity.index).gen)
		{
			auto f = std::bind(&World::despawnEntity, this, entity.index);
			commands.push_back(f);
		}
		return this;
	}

	void World::CallCommands()
	{
		auto commandsLength = scast<u32>(commands.size());
		for (u32 i = 0; i < commandsLength; i++)
		{
			commands.front()();
			commands.pop_front();
		}
	}

	void World::despawnEntity(u32 index)
	{
		despawnedEntities.push_back(index);
		currentEntities.at(index).gen++;
		for (auto& pair : ComponentsMap)
		{
			pair.second->clear(index);
		}
		queriesDirty = true;
	}

}