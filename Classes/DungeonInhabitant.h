#pragma once

// interfaces
#include "interfaces/MoveableInterface.h"

namespace AttackOfSlime 
{
	// forward declarations
	class DungeonTile;

	/// <summary>
	/// A single inhabitant of the dungeon, and which tile they inhabit.
	/// </summary>
	struct DungeonInhabitant
	{
		MoveableInterface* inhabitant;
		DungeonTile* tile;
	};
}
