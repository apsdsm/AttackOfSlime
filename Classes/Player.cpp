// classes
#include "Player.h"
#include "Dungeon.h"
#include "GameUI.h"
#include "Slime.h"
#include "SceneManager.h"

// services
#include "services\DirectoryService.h"

// effects
#include "effects/ShakeEffect.h"

// using namespaces
using namespace cocos2d;
using namespace CocosDenshion;
using namespace AttackOfSlime;


/// <summary>
/// Creates a new player object, or deletes instance and returns nullptr if
/// anything goes wrong.
/// </summary>
/// <param name="dungeon">dungeon the player will inhabit</param>
/// <returns>reference to new player object</returns>
Player* Player::create(Dungeon *dungeon)
{
	Player* instance = new Player();

	if ( instance->initWithSpriteFrameName( "Characters/Player.png" ) )
	{
		instance->autorelease();
		instance->initOptions(dungeon);
		instance->scheduleUpdate();
		return instance;
	}

	CC_SAFE_DELETE( instance );

	return nullptr;
}


/// <summary>
/// Updates the player each frame.
/// </summary>
/// <param name="deltaTime">time elapsed since last update</param>
void Player::update( float deltaTime )
{
	timeSinceAction += deltaTime;

	if ( receivingDamage )
	{
		runAction( ShakeEffect::withDuration( 0.1f ) );
		receivingDamage = false;
	}
}


/// <summary>
/// Move the player to the specified position.
/// </summary>
/// <param name="position">coords to move player to</param>
void Player::moveToPosition( cocos2d::Vec2 position )
{
	this->setPosition( position );
}


/// <summary>
/// Damage the player by the specified amount. If the player health drops to
/// zero, will load the game over screen.
/// </summary>
/// <param name="damageAmmount">amount to lower the player's health</param>
void Player::damage( int damageAmmount )
{
	receivingDamage = true;

	health -= damageAmmount;

	if ( health <= 0 )
	{
		SceneManager::getInstance()->switchToScene( SceneManager::Scenes::GameOver );
		return;
	}

	GameUI* gameUI = (GameUI*)DirectoryService::getInstance()->lookUp( "GameUI" );
	gameUI->setDirty();
}


/// <summary>
/// Get the player's current health.
/// </summary>
/// <returns>player's current health</returns>
int Player::getHealth()
{
	return health;
}


/// <summary>
/// Initialize the player.
/// </summary>
/// <param name="dungeon">dungeon the player is tied to</param>
void Player::initOptions(Dungeon* dungeon)
{
	// copy dungeon reference
	this->dungeon = dungeon;

	// scale up 200%
	this->setScale( 2.0f );

	// top left corner anchor
	this->setAnchorPoint( Vec2( 0, 1 ) );

	// set texture for no antialiasing
	this->_texture->setAliasTexParameters();

	// get reference to audio engine
	this->audio = SimpleAudioEngine::getInstance();

	// map different keys to possible directions of movement
	keyMap[ EventKeyboard::KeyCode::KEY_W ] = Direction::Up;
	keyMap[ EventKeyboard::KeyCode::KEY_A ] = Direction::Left;
	keyMap[ EventKeyboard::KeyCode::KEY_S ] = Direction::Down;
	keyMap[ EventKeyboard::KeyCode::KEY_D ] = Direction::Right;

	// keyboard listener
	auto keylistener = cocos2d::EventListenerKeyboard::create();
	keylistener->onKeyPressed = CC_CALLBACK_2( Player::onKeyboardEvent, this );

	// add listeners to dispatcher
	cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority( keylistener, this );

	// add player to directory
	DirectoryService::getInstance()->registerNode( "Player", this );
}

/// <summary>
/// Called on keyboard events. Checks to see if player will move into an empty
/// tile or attack a slime.
/// </summary>
/// <param name="keyCode">key that was pressed</param>
/// <param name="event">event reference</param>
void Player::onKeyboardEvent( EventKeyboard::KeyCode keyCode, Event* event )
{
	if ( keyMap.find( keyCode ) == keyMap.end() )
	{
		return;
	}

	Direction direction = keyMap[ keyCode ];

	DungeonTile* adjacentTile = dungeon->getAdjacentTile( this, direction );

	if ( timeSinceAction > actionCooldown && adjacentTile != nullptr ) {

		if ( adjacentTile->inhabitant != nullptr )
		{
			Slime* slime = ( Slime* ) adjacentTile->inhabitant;

			Vec2 towardSlime = slime->getPosition() - getPosition();

			towardSlime.clamp( Vec2( -10, -10 ), Vec2( 10, 10 ) );

			auto move = MoveBy::create( 0.05f, towardSlime );

			auto damagePlayer = CallFunc::create( [ = ]() {
				audio->playEffect( "Sfx/playerattack_sfx.wav" );
				slime->damage( attackStrength );
			} );

			auto moveback = MoveBy::create( 0.05f, -towardSlime );

			auto seq = Sequence::create( move, damagePlayer, moveback, nullptr );

			runAction( seq );
		} else if ( adjacentTile->passable && !receivingDamage )
		{
			audio->playEffect( "Sfx/move_sfx.wav" );
			dungeon->moveToTile( this, adjacentTile );
		}

		timeSinceAction = 0;
	}
}
