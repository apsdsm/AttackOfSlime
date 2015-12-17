// classes
#include "SceneManager.h"
#include "GameOverLayer.h"

// cocos2d
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "SimpleAudioEngine.h"

// using namespaces
using namespace cocos2d;
using namespace CocosDenshion;
using namespace AttackOfSlime;

/// <summary>
/// Set up the layer.
/// </summary>
/// <returns></returns>
bool GameOverLayer::init()
{
	if ( !Layer::init() )
	{
		return false;
	}

	// add scenes to layer
	auto gameOverNode = CSLoader::createNode( "GameOver.csb" );
	addChild( gameOverNode );
}

/// <summary>
/// Called when the layer enters the stage.
/// </summary>
void GameOverLayer::onEnter()
{
	Layer::onEnter();

	// set up event listeners
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2( GameOverLayer::onKeyboardEvent, this );

	// add events - they'll be removed when the node is destroyed
	getEventDispatcher()->addEventListenerWithSceneGraphPriority( listener, this );

	// pause music and play death sound
	SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	SimpleAudioEngine::getInstance()->playEffect( "Sfx/dead_sfx.wav" );
}

/// <summary>
/// Called when the layer exits the stage
/// </summary>
void GameOverLayer::onExit()
{
	Layer::onExit();
}


/// <summary>
/// Event handler for keyboard events. If user hits space, go back to the main
/// menu.
/// </summary>
/// <param name="keyCode">key that was pressed</param>
/// <param name="event">event object reference</param>
void GameOverLayer::onKeyboardEvent( EventKeyboard::KeyCode keyCode, Event* event )
{
	if ( keyCode == EventKeyboard::KeyCode::KEY_SPACE )
	{
		SceneManager::getInstance()->switchToScene( SceneManager::Scenes::StartMenu );
	}
}