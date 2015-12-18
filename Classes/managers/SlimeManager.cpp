// dependencies
#include "SlimeManager.h"
#include "Dungeon.h"
#include "Slime.h"
#include "GameUI.h"

// structures
#include "structures/DungeonTile.h"

// services
#include "services/DirectoryService.h"
#include "services/ScoreService.h"

// namespaces
using namespace AttackOfSlime;

/// <summary>
/// Will set the manager to update each frame.
/// </summary>
/// <returns>True if successfully initialized.</returns>
bool SlimeManager::init()
{
	if ( !Node::init() )
	{
		return false;
	}

	this->scheduleUpdate();

	return true;
}


/// <summary>
/// If enough time has passed since the last slime was spawned, will spawn a new one.
/// </summary>
/// <param name="deltaTime"></param>
void SlimeManager::update( float deltaTime )
{
	timeSinceSpawn += deltaTime;

	while ( timeSinceSpawn > spawnCooldown )
	{
		spawnNewSlime();
		timeSinceSpawn -= spawnCooldown;
	}
}


/// <summary>
/// Asks for a random free tile in the dungeon, and if one is provided, will spawn a
/// new slime there.
/// </summary>
void SlimeManager::spawnNewSlime()
{
	Dungeon *dungeon = ( Dungeon* ) DirectoryService::getInstance()->lookUp( "Dungeon" );

	DungeonTile* freeTile = dungeon->getRandomFreeTile();

	if ( freeTile != nullptr )
	{
		auto slime = Slime::create( this );

		slimes.push_back( slime );

		dungeon->addChild( slime );

		dungeon->addToDungeon( freeTile->coords, slime );
	}
}


/// <summary>
/// Will remove the slime from the dungeon, add points for its death to the score, and
/// finally tell the slime to erase itself from the game.
/// </summary>
/// <param name="deadSlime">Reference to the slime that should be destroyed</param>
void SlimeManager::notifyOfDeath( Slime* deadSlime )
{
	Dungeon *dungeon = ( Dungeon* ) DirectoryService::getInstance()->lookUp( "Dungeon" );
	
	GameUI *gameUI = ( GameUI* ) DirectoryService::getInstance()->lookUp( "GameUI" );

	ScoreService::getInstance()->addPointsToScore( deadSlime->getScoreModifier() );

	gameUI->setDirty();

	dungeon->removeFromDungeon( deadSlime );
	
	deadSlime->removeFromParentAndCleanup( true );
	
	slimes.erase(std::remove(slimes.begin(), slimes.end(), deadSlime), slimes.end());
}