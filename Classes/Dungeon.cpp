// dependencies
#include "Dungeon.h"
#include "Player.h"
#include "Slime.h"
#include "GameUI.h"

// structures
#include "DungeonTile.h"

// managers
#include "managers/SlimeManager.h"

// services
#include "services/DirectoryService.h"

// interfaces
#include "interfaces/MoveableInterface.h"

// using namespaces
using namespace cocos2d;
using namespace AttackOfSlime;


/// <summary>
/// Sets up the Tiled map (creates an abstract representation of all the tiles, and adds
/// metadata about which tiles are passable), and adds the dungeon to the node directory.
/// </summary>
void Dungeon::onEnter()
{
	Node::onEnter();

	// get reference to the map object
	map = this->getChildByName<TMXTiledMap*>( "Map" );

	// get map info
	Size mapSize = map->getMapSize();
	Size tileSize = map->getTileSize();

	// copy tile sizes
	mapRows = mapSize.height;
	mapCols = mapSize.width;
	mapScale = map->getScale();
	tileWidth = tileSize.width;
	tileHeight = tileSize.height;

	// get values to centre map
	Size windowSize = Director::getInstance()->getWinSize();

	// save screen position of dungeon
	dungeonScreenPos = Vec2( 0, 0 );

	// save the position of the origin pixel (top left corner of map)
	dungeonOriginPixel = Vec2( 0, windowSize.height );

	// load the blockers layer of the map (use this to check which tiles are passable)
	TMXLayer* blockers = map->getLayer( "blockers" );

	// reserves enough memory for each of the tile objects
	tiles.reserve( mapSize.width * mapSize.height );

	// check to see which tiles are passable
	for ( auto col = 0; col < mapSize.width; col++ )
	{
		for ( auto row = 0; row < mapSize.height; row++ )
		{
			auto tile = new DungeonTile();

			Sprite* tileSprite = blockers->getTileAt( Vec2( col, row ) );

			tile->passable = tileSprite == nullptr;

			tile->coords = Vec2( col, row );

			tiles.push_back( tile );
		}
	}

	// register with the directory service
	DirectoryService::getInstance()->registerNode( "Dungeon", this );
}


/// <summary>
/// Add an entity to the dungeon at the specified location.
/// </summary>
/// <param name="coords">coordinates of the tile to add the entity</param>
/// <param name="entity">reference to the entity</param>
/// <returns>true if entity successfully added</returns>
bool Dungeon::addToDungeon( Vec2 coords, MoveableInterface* entity )
{
	DungeonInhabitant* inhabitant = getInhabitant( entity );
	DungeonTile* tile = getTileAt( coords );

	bool canAddToDungeon = ( inhabitant == nullptr && tile->passable && tile->inhabitant == nullptr );

	if ( canAddToDungeon ) {
		tile->inhabitant = entity;

		inhabitant = new DungeonInhabitant();
		inhabitant->inhabitant = entity;
		inhabitant->tile = tile;
		
		inhabitants.push_back( inhabitant );
	}

	entity->moveToPosition( getTilePosition( coords ) );

	return false;
}


/// <summary>
/// Removes an inhabitant from the dungeon.
/// </summary>
/// <param name="entity">reference to the entity to remove</param>
void Dungeon::removeFromDungeon( MoveableInterface* entity )
{
	DungeonInhabitant* inhabitant = getInhabitant( entity );

	if ( inhabitant != nullptr )
	{
		inhabitant->tile->inhabitant = nullptr;
		inhabitants.erase( std::remove( inhabitants.begin(), inhabitants.end(), inhabitant ), inhabitants.end() );
	}
}


/// <summary>
/// Returns the position of a tile in pixels
/// </summary>
/// <param name="coords">Coords of the tile to query</param>
/// <returns>location of specified tile in pixels</returns>
cocos2d::Vec2 Dungeon::getTilePosition( cocos2d::Vec2 coords )
{
	// if valid coords
	if ( coords.x >= mapCols || coords.x < 0 || coords.y >= mapRows || coords.y < 0 )
	{
		return cocos2d::Vec2();
	}

	// get the position of the tile
	int x = dungeonOriginPixel.x + (coords.x * tileWidth * mapScale);
	int y = dungeonOriginPixel.y - (coords.y * tileHeight * mapScale);

	// return as Vec2
	return cocos2d::Vec2( x, y );
}


/// <summary>
/// Returns the tile adjacent to the entity in the given direction.
/// </summary>
/// <param name="entity"></param>
/// <param name="direction"></param>
/// <returns></returns>
DungeonTile* Dungeon::getAdjacentTile( MoveableInterface* entity, Direction direction )
{
	// if it's not in the entity list, baby I don't want to know
	DungeonInhabitant* inhabitant = getInhabitant( entity );

	if ( inhabitant == nullptr ) {
		return nullptr;
	}

	Vec2 adjacentCoords = Vec2::ZERO;

	if ( direction == Direction::Right ) {
		adjacentCoords = Vec2( inhabitant->tile->coords.x + 1, inhabitant->tile->coords.y );
	}
	else if ( direction == Direction::Left ) {
		adjacentCoords = Vec2( inhabitant->tile->coords.x - 1, inhabitant->tile->coords.y );
	}

	else if ( direction == Direction::Up ) {
		adjacentCoords = Vec2( inhabitant->tile->coords.x, inhabitant->tile->coords.y -1 );
	}
	else if ( direction == Direction::Down ) {
		adjacentCoords = Vec2( inhabitant->tile->coords.x, inhabitant->tile->coords.y + 1 );
	}
	else {
		return nullptr;
	}

	return getTileAt( adjacentCoords );
}

/// <summary>
/// Move the entity to the specified tile.
/// </summary>
/// <param name="entity"></param>
/// <param name="tile"></param>
void Dungeon::moveToTile( MoveableInterface * entity, DungeonTile * tile )
{
	DungeonInhabitant* inhabitant = getInhabitant( entity );

	if ( inhabitant != nullptr && tile->inhabitant == nullptr && tile->passable == true ){
		
		// no longer here...
		inhabitant->tile->inhabitant = nullptr;
		
		// ...but here
		inhabitant->tile = tile;
		tile->inhabitant = entity;
		entity->moveToPosition( getTilePosition( tile->coords ) );
	}
}


/// <summary>
/// Return an array of the tiles around the entity. 
/// </summary>
/// <param name="mover">The entity to look for tiles around</param>
std::vector<DungeonTile*> Dungeon::getTilesAroundEntity( MoveableInterface * mover )
{
	DungeonInhabitant* inhabitant = getInhabitant( mover );

	std::vector<DungeonTile*> surroundingTiles;

	if ( inhabitant == nullptr )
	{
		return surroundingTiles;
	}

	// reserve space
	surroundingTiles.reserve( 4 );

	// generate the coords surrounding this tile
	std::vector<Vec2> surroundingTileCoords;
	surroundingTileCoords.reserve( 4 );
	surroundingTileCoords.push_back( Vec2( inhabitant->tile->coords.x, inhabitant->tile->coords.y - 1 ) );
	surroundingTileCoords.push_back( Vec2( inhabitant->tile->coords.x, inhabitant->tile->coords.y + 1 ) );
	surroundingTileCoords.push_back( Vec2( inhabitant->tile->coords.x - 1, inhabitant->tile->coords.y ) );
	surroundingTileCoords.push_back( Vec2( inhabitant->tile->coords.x + 1, inhabitant->tile->coords.y ) );

	// for each set of coords, get that tile if it exists
	for ( Vec2 coords : surroundingTileCoords )
	{
		DungeonTile* potentialTile = getTileAt( coords );
		
		if ( potentialTile != nullptr )
		{
			surroundingTiles.push_back( potentialTile );
		}
	}

	return surroundingTiles;
}


/// <summary>
/// Return the coordinates for an entity in the dungeon.
/// </summary>
/// <param name="entity"></param>
/// <returns></returns>
Vec2 Dungeon::getEntityCoords( MoveableInterface* entity )
{
	DungeonInhabitant* inhabitant = getInhabitant( entity );
	
	if ( inhabitant != nullptr )
	{
		return inhabitant->tile->coords;
	}

	return nullptr;
}


/// <summary>
/// checks to see if there are any free tiles, then provides one at random.
/// </summary>
/// <returns></returns>
DungeonTile* Dungeon::getRandomFreeTile()
{
	std::vector<DungeonTile*> freeTiles;

	freeTiles.reserve( tiles.size() );

	for ( auto tile : tiles )
	{
		if ( tile->passable && tile->inhabitant == nullptr )
		{
			freeTiles.push_back( tile );
		}
	}

	if ( freeTiles.size() > 0 )
	{
		int randomIndex = rand() % freeTiles.size();
		return freeTiles[ randomIndex ];
	}

	return nullptr;
}


/// <summary>
/// Return the tile at the given row and col.
/// </summary>
/// <param name="row">row to query</param>
/// <param name="col">col to query</param>
/// <returns>pointer to the correct tile</returns>
DungeonTile* Dungeon::getTileAt( cocos2d::Vec2 coords )
{
	int index = coords.x * mapRows + coords.y;

	if ( index <= tiles.size() && index >= 0 ) {
		return tiles[ index ];
	}

	return nullptr;
}

/// <summary>
/// Return the dungeon inhabitant object for the given entity, or a nullptr.
/// </summary>
/// <param name="entity"></param>
/// <returns></returns>
DungeonInhabitant * Dungeon::getInhabitant( MoveableInterface * entity )
{
	// check if the entity is in the entity list
	DungeonInhabitant* inhabitant = nullptr;

	for ( auto subject : inhabitants ) {
		if ( subject->inhabitant == entity ) {
			inhabitant = subject;
			break;
		}
	}

	return inhabitant;
}
