// dependencies
#include "GameOverScene.h"

// services
#include "services/SceneService.h"

// cocos2d
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "SimpleAudioEngine.h"

// using namespaces
using namespace cocos2d;
using namespace CocosDenshion;
using namespace AttackOfSlime;

/// <summary>
/// Sets up the game over scene:
/// - loads scene data and adds it to the parent node
/// - adds keyboard event listener
/// - stops background music and plays the death sound
/// </summary>
void GameOverScene::onEnter()
{
	Scene::onEnter();

	// add load the scene data and attach to the actual scene
	auto gameOverScene = CSLoader::createNode( "GameOver.csb" );
	addChild( gameOverScene );

	// set up event listeners
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2( GameOverScene::onKeyboardEvent, this );

	// add events - they'll be removed when the node is destroyed
	getEventDispatcher()->addEventListenerWithSceneGraphPriority( listener, this );

	// pause music and play death sound
	SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	SimpleAudioEngine::getInstance()->playEffect( "Sfx/dead_sfx.wav" );
}

/// <summary>
/// If the player presses the space bar, will return them to the main menu.
/// </summary>
/// <param name="keyCode">key that was pressed</param>
/// <param name="event">reference to event</param>
void GameOverScene::onKeyboardEvent( EventKeyboard::KeyCode keyCode, Event* event )
{
	if ( keyCode == EventKeyboard::KeyCode::KEY_SPACE )
	{
		SceneService::getInstance()->switchToScene( SceneService::Scenes::StartMenu );
	}
}