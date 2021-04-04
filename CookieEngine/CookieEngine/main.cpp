#include <optional>
#include "World.h"

int main()
{
	cookie::World world {};
	world.SpawnEntity(cookie::Position {}, cookie::temp_rotation {});
}