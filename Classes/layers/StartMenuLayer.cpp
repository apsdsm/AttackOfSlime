// classes
#include "StartMenuLayer.h"
#include "SceneManager.h"

// cocos2d
#include "cocos2d.h"
#include "cocostudio\CocoStudio.h"
#include "SimpleAudioEngine.h"

// using namespaces
using namespace cocos2d;
using namespace CocosDenshion;
using namespace AttackOfSlime;

/// <summary>
/// Set up the layer.
/// </summary>
/// <returns></returns>
bool StartMenuLayer::init()
{
	if ( !Layer::init() )
	{
		return false;
	}

	// load scenes and add as children
	auto startMenuNode = CSLoader::createNode( "StartMenu.csb" );
	addChild( startMenuNode );
}

void StartMenuLayer::onEnter()
{
	Layer::onEnter();

	// set up event listeners
	keyboardEventListener = cocos2d::EventListenerKeyboard::create();
	keyboardEventListener->onKeyPressed = CC_CALLBACK_2( StartMenuLayer::onKeyboardEvent, this );

	// add events - they'll be removed when the node is destroyed
	auto eventDispatcher = Director::getInstance()->getEventDispatcher();
	getEventDispatcher()->addEventListenerWithSceneGraphPriority( keyboardEventListener, this );

	// play music
	SimpleAudioEngine::getInstance()->playBackgroundMusic( "Music/startmenu_bgm.wav", true );
}

void StartMenuLayer::onExit()
{
	Layer::onExit();
}

/// <summary>
/// Event handler for keyboard events. If spacebar is pressed, will change to
/// the game scene.
/// </summary>
/// <param name="keyCode">key that was pressed</param>
/// <param name="event">event object reference</param>
void StartMenuLayer::onKeyboardEvent( cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event )
{
	if ( keyCode == EventKeyboard::KeyCode::KEY_SPACE )
	{
		SceneManager::getInstance()->switchToScene( SceneManager::Scenes::Game );
	}
}
