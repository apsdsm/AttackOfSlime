#pragma once

// cocos2d
#include "cocos2d.h"

// interfaces
#include "interfaces/MoveableInterface.h"

// using namespaces
using namespace cocos2d;

namespace AttackOfSlime {

	/// <summary>
	/// A single tile in the dungeon. Stores information about each tile, and
	/// stores a reference to any inhabiting entity.
	/// </summary>
	struct DungeonTile
	{
		bool passable;
		MoveableInterface* inhabitant;
		Vec2 coords;
	};
}
