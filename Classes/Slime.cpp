// classes
#include "Slime.h"
#include "Dungeon.h"
#include "Player.h"

// effects
#include "effects/ShakeEffect.h"

// services
#include "services/DirectoryService.h"

// managers
#include "managers/SlimeManager.h"

// using namespaces
using namespace AttackOfSlime;


/// <summary>
/// Creates a new slime
/// </summary>
/// <param name="dungeon"></param>
/// <returns></returns>
Slime* Slime::create( Dungeon* dungeon, SlimeManager* factory )
{
	Slime* instance = new Slime();

	if ( instance->initWithSpriteFrameName( "Characters/Slime.png" ) )
	{
		instance->autorelease();
		instance->initialize( dungeon, factory );
		instance->scheduleUpdate();
	
		return instance;
	}
	else
	{
		CC_SAFE_DELETE( instance );
		return nullptr;
	}
}

/// <summary>
/// Initialize the slime.
/// </summary>
/// <param name="dungeon">the dungeon that this slime inhabits</param>
void Slime::initialize( Dungeon* dungeon, SlimeManager* factory )
{
	//this->dungeon = dungeon;

	this->manager = factory;

	this->audio = SimpleAudioEngine::getInstance();

	this->setScale( 2.0f );

	this->setAnchorPoint( Vec2( 0, 1 ) );

	this->_texture->setAliasTexParameters();

	this->moveHistory.reserve( 5 );
}

/// <summary>
/// Update the slime. When the cool down has timed out, will move the slime towards the player.
/// </summary>
/// <param name="deltaTime">How much time passed since last action</param>
void Slime::update( float deltaTime )
{
	if ( receivingDamage )
	{
		runAction( ShakeEffect::withDuration( 0.2f ) );

		receivingDamage = false;

		timeToRecovery = recoveryCooldown;
	}
	else if ( timeToRecovery > 0 )
	{
		timeToRecovery -= deltaTime;
	}
	else
	{
		timeSinceAction += deltaTime;

		while ( timeSinceAction > actionCooldown )
		{
			Dungeon* dungeon = ( Dungeon* ) DirectoryService::getInstance()->lookUp( "Dungeon" );
			
			Player* player = ( Player* ) DirectoryService::getInstance()->lookUp( "Player" );
			
			std::vector<DungeonTile*> surroundingTiles = dungeon->getTilesAroundEntity( this );
			
			Vec2 playerPosition = dungeon->getEntityCoords( player );

			bool canAttackPlayer = false;

			std::vector<PotentialMove*> potentialMoves;
			
			potentialMoves.reserve( 4 );

			for ( auto tile : surroundingTiles )
			{
				if ( playerPosition == tile->coords )
				{
					canAttackPlayer = true;
					break;
				} 
				else if ( tile->inhabitant == nullptr && tile->passable == true )
				{
					auto potentialMove = new PotentialMove();

					potentialMove->tile = tile;

					// tiles that take the slime closer to the player are cheaper than tiles that that the slime farther away
					potentialMove->cost = tile->coords.distance( playerPosition );

					// the more recently a tile was in movement history, the less inclined the slime is to go there
					for ( int i = 0; i < moveHistory.size(); i++ )
					{
						if ( tile == moveHistory[ i ] )
						{
							potentialMove->cost += i;
						}
					}

					potentialMoves.push_back( potentialMove );
				}
			}

			if ( canAttackPlayer )
			{

				Vec2 towardPlayer = player->getPosition() - getPosition();

				towardPlayer.clamp( Vec2( -10, -10 ), Vec2( 10, 10 ) );

				auto move = MoveBy::create( 0.2f, towardPlayer );

				auto damagePlayer = CallFunc::create( [ = ]() {
					audio->playEffect( "Sfx/slimeattack_sfx.wav" );
					player->damage( attackStrength );
				} );

				auto moveback = MoveBy::create( 0.2f, -towardPlayer );

				auto seq = Sequence::create( move, damagePlayer, moveback, nullptr );

				runAction( seq );
			}
			else if ( potentialMoves.size() > 0 )
			{
				// find cheapest move
				auto nextMove = potentialMoves[ 0 ];

				for ( int i = 1; i < potentialMoves.size(); i++ )
				{
					if ( potentialMoves[ i ]->cost < nextMove->cost )
					{
						nextMove = potentialMoves[ i ];
					}
				}

				// slime is only allowed to have memory of 5 tiles
				if ( moveHistory.size() > 5 )
				{
					moveHistory.erase( moveHistory.begin() );
				}

				// add this next move to the slime's memory
				moveHistory.push_back( nextMove->tile );

				// move slime to new position
				dungeon->moveToTile( this, nextMove->tile );
			}

			// reset the timer
			timeSinceAction -= actionCooldown;
		}
	}
}

/// <summary>
/// Move the slime to a specific position
/// </summary>
/// <param name="position"></param>
void Slime::moveToPosition( Vec2 position )
{
	this->setPosition( position );
}

/// <summary>
/// Damage the slime by the specified amount. If the slime is near death, set
/// its low health sprite.
/// </summary>
/// <param name="damageAmmount">by how much</param>
void Slime::damage( int damageAmmount )
{	
	receivingDamage = true;

	health -= damageAmmount;

	if ( health <= 0 )
	{
		manager->notifyOfDeath( this );
	}
	else if ( health <= 10 )
	{
		setSpriteFrame( "Characters/SlimeLowHealth.png" );
	}
}

/// <summary>
/// Returns the score modifier - this is the value that killing the slime will
/// modify the score by.
/// </summary>
/// <returns>amount to modify the score</returns>
int Slime::getScoreModifier()
{
	return scoreModifier;
}
