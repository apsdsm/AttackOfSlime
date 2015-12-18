#pragma once

// cocos2d
#include "cocos2d.h"
#include "2d\CCTMXTiledMap.h"

// structures
#include "DungeonTile.h"
#include "DungeonInhabitant.h"

// enumerations
#include "enumerations/Direction.h"

// interfaces
#include "interfaces/MoveableInterface.h"

// namespaces
using namespace cocos2d;

namespace AttackOfSlime
{
	// forward declarations
	class Player;
	class Slime;
	class GameUI;
	class SlimeManager;

	/// <summary>
	/// The dungeon is the main playing field for the game. It converts a Tiled map into an
	/// abstract representation of tiles, which the player and the enemies can move around.
	/// The dungeon is responsible for keeping track of each entity's location, as well as
	/// for providing information about the current tile landscape.
	/// </summary>
	class Dungeon : public cocos2d::Node
	{
	public:
	
		// create a new dungeon
		CREATE_FUNC( Dungeon );

		// called when dungeon enters scene
		virtual void onEnter() override;

		// add an entity to the dungeon
		bool addToDungeon( cocos2d::Vec2 coords, MoveableInterface* entity );

		// remove an entity from the dungeon
		void removeFromDungeon( MoveableInterface* entity );

		// get the pixel position of a tile
		cocos2d::Vec2 getTilePosition( cocos2d::Vec2 coords );

		// return the tile adjacent to an entity in a given direction
		DungeonTile* getAdjacentTile( MoveableInterface* entity, Direction direction );

		// move an entity to a specific tile.
		void moveToTile( MoveableInterface* entity, DungeonTile* tile );

		// return the free tiles above, below, left, and right of the mover
		std::vector<DungeonTile*> getTilesAroundEntity( MoveableInterface* mover );

		// return the coordinates of a given entity in the dungeon
		cocos2d::Vec2 getEntityCoords( MoveableInterface* entity );

		// return a random free tile
		DungeonTile* getRandomFreeTile();

	private:

		// map used by dungeon
		cocos2d::TMXTiledMap* map;

		// references to all tiles in dungeon
		std::vector<DungeonTile*> tiles;

		// references to all inhabitants in dungeon
		std::vector<DungeonInhabitant*> inhabitants;

		// number of tile rows in map
		int mapRows;

		// number of tile columns in map
		int mapCols;

		// zoom scale for map
		float mapScale;

		// width of tile in pixels
		int tileWidth;

		// height of tile in pixels
		int tileHeight;

		// the point at which the dungeon is placed on the screen
		cocos2d::Vec2 dungeonScreenPos;

		// the pixel position of the 0,0 tile in the dungeon
		cocos2d::Vec2 dungeonOriginPixel;

		// gets the tile at the provided map tile coords
		DungeonTile* getTileAt( cocos2d::Vec2 coords );

		// gets the inhabitant that matches the provided entity
		DungeonInhabitant* getInhabitant( MoveableInterface* entity );
	};
}
