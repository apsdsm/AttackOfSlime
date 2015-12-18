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
/// Map key codes to directions.
/// </summary>
std::map<EventKeyboard::KeyCode, Direction> Player::keyMap = {
	{ EventKeyboard::KeyCode::KEY_W, Direction::Up },
	{ EventKeyboard::KeyCode::KEY_A, Direction::Left},
	{ EventKeyboard::KeyCode::KEY_S, Direction::Down},
	{ EventKeyboard::KeyCode::KEY_D, Direction::Right}
};

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
/// Set up internal values. Doubles pixel size, removes smooth antialiasing, and puts the
/// anchor in the top left to make it easier to position on the tiled map coords.
/// </summary>
/// <param name="dungeon">dungeon the player is tied to</param>
void Player::initOptions(Dungeon* dungeon)
{
	this->dungeon = dungeon;
	this->setScale( 2.0f );
	this->setAnchorPoint( Vec2( 0, 1 ) );
	this->_texture->setAliasTexParameters();
}

/// <summary>
/// Get external references, and set up events.
/// </summary>
void Player::onEnter()
{
	Sprite::onEnter();

	this->audio = SimpleAudioEngine::getInstance();
	
	// create keyboard listeners
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
