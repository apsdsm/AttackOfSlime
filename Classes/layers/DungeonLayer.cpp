// dependencies
#include "DungeonLayer.h"
#include "Player.h"
#include "Dungeon.h"

// managers
#include "managers/SlimeManager.h"

// readers
#include "DungeonReader.h"
#include "readers/GameUIReader.h"

//cocos2d
#include "cocos2d.h"
#include "cocostudio\CocoStudio.h"
#include "SimpleAudioEngine.h"

// using namespaces
using namespace cocos2d;
using namespace cocostudio::timeline;
using namespace CocosDenshion;
using namespace AttackOfSlime;

bool DungeonLayer::init()
{
	if ( !Layer::init() )
	{
		return false;
	}

	// register class readers required to load the scene
	auto loaderInstance = CSLoader::getInstance();
	loaderInstance->registReaderObject( "DungeonReader", ( ObjectFactory::Instance )DungeonReader::getInstance );
	loaderInstance->registReaderObject( "GameUIReader", ( ObjectFactory::Instance )GameUIReader::getInstance );
}

void DungeonLayer::onEnter()
{
	Layer::onEnter();

	// load the scene
	auto dungeonNode = CSLoader::createNode( "Game.csb" );
	addChild( dungeonNode );

	Dungeon* dungeon = (Dungeon*)dungeonNode->getChildByName( "Dungeon" );

	// add the slime manager
	auto slimeManager = SlimeManager::create();
	addChild( slimeManager );

	// add the player
	auto player = Player::create( dungeon );
	addChild( player );
	dungeon->addToDungeon( cocos2d::Vec2( 1, 3 ), player );

	// set up event listeners
	keyboardEventListener = cocos2d::EventListenerKeyboard::create();
	keyboardEventListener->onKeyPressed = CC_CALLBACK_2( DungeonLayer::onKeyboardEvent, this );

	// add events - they'll be removed when the node is destroyed
	auto eventDispatcher = Director::getInstance()->getEventDispatcher();
	getEventDispatcher()->addEventListenerWithSceneGraphPriority( keyboardEventListener, this );

	// play music
	SimpleAudioEngine::getInstance()->playBackgroundMusic( "Music/dungeon_bgm.wav", true );
}

void DungeonLayer::onExit()
{
	Layer::onExit();
}

/// <summary>
/// Event handler for keyboard events. If spacebar is pressed, will change to
/// the game scene.
/// </summary>
/// <param name="keyCode">key that was pressed</param>
/// <param name="event">event object reference</param>
void DungeonLayer::onKeyboardEvent( cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event )
{
	if ( keyCode == EventKeyboard::KeyCode::KEY_P )
	{
		CCLOG( "player wants to pause" );
	}
}
