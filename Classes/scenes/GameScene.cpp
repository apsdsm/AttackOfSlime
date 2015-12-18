// dependencies
#include "GameScene.h"
#include "Player.h"
#include "Dungeon.h"

// managers
#include "managers/SlimeManager.h"

// services
#include "services/ScoreService.h"

// cocos2d
#include "cocos2d.h"
#include "cocostudio\CocoStudio.h"

// namespaces
using namespace cocos2d;
using namespace cocostudio::timeline;
using namespace AttackOfSlime;


/// <summary>
/// Sets up the game scene:
/// - loads scene data and adds it to the parent node
/// - loads the slime manager node
/// - loads the player node
/// - adds keyboard event listener so player can pause the game
/// - stops the intro music and plays the game music
/// - resets the score to zero
/// </summary>
void GameScene::onEnter()
{
	Scene::onEnter();

	// load game scene data and attach as child node of actual scene
	auto scene = ( Scene* ) CSLoader::createNode( "Game.csb" );
	addChild(scene);

	// get the dungeon
	Dungeon* dungeon = ( Dungeon* ) scene->getChildByName( "Dungeon" );

	// add the slime manager
	auto slimeManager = SlimeManager::create();
	dungeon->addChild( slimeManager );

	// add the player
	auto player = Player::create( dungeon );
	scene->addChild( player );
	dungeon->addToDungeon( cocos2d::Vec2( 1, 3 ), player );

	// set up event listeners
	auto keyboardEventListener = cocos2d::EventListenerKeyboard::create();
	keyboardEventListener->onKeyPressed = CC_CALLBACK_2( GameScene::onKeyboardEvent, this );

	// add events to dispatcher
	auto eventDispatcher = Director::getInstance()->getEventDispatcher();
	getEventDispatcher()->addEventListenerWithSceneGraphPriority( keyboardEventListener, this );

	// play music
	SimpleAudioEngine::getInstance()->playBackgroundMusic( "Music/dungeon_bgm.wav", true );

	// reset score
	ScoreService::getInstance()->resetScore();
}

void GameScene::onKeyboardEvent( EventKeyboard::KeyCode keyCode, Event* event )
{
	if ( keyCode == EventKeyboard::KeyCode::KEY_P )
	{
		CCLOG( "player wants to pause" );
	}
}