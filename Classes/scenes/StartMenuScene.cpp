// dependencies
#include "StartMenuScene.h"

// managers
#include "SceneManager.h"

// cocos2d
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "SimpleAudioEngine.h"

// using namespaces
using namespace cocos2d;
using namespace CocosDenshion;
using namespace AttackOfSlime;


/// <summary>
/// Sets up the start menu scene:
/// - loads scene data and adds it to the parent node
/// - adds keyboard event listener
/// - starts playing the intro scene music
/// </summary>
void StartMenuScene::onEnter()
{
	Scene::onEnter();

	// load the scene data and add it to the parent node
	auto scene = CSLoader::createNode( "StartMenu.csb" );
	addChild( scene );

	// set up event listeners
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2( StartMenuScene::onKeyboardEvent, this );

	// add events to dispatcher
	getEventDispatcher()->addEventListenerWithSceneGraphPriority( listener, this );

	// pause music
	SimpleAudioEngine::getInstance()->playBackgroundMusic( "Music/startmenu_bgm.wav", true );
}


/// <summary>
/// If the player presses the spacebar, a new game will start.
/// </summary>
/// <param name="keyCode">key that was pressed</param>
/// <param name="event">event object reference</param>
void StartMenuScene::onKeyboardEvent( EventKeyboard::KeyCode keyCode, Event* event )
{
	if ( keyCode == EventKeyboard::KeyCode::KEY_SPACE )
	{
		SceneManager::getInstance()->switchToScene( SceneManager::Scenes::Game );
	}
}
