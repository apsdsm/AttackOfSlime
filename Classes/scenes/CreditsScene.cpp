// dependencies
#include "CreditsScene.h"

// services
#include "services/SceneService.h"

// cocos2d
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"

// using namespaces
using namespace cocos2d;
using namespace AttackOfSlime;

/// <summary>
/// Sets up the credits scene:
/// - load scene data and adds it to the parent node
/// - adds keyboard event listener
/// </summary>
void CreditsScene::onEnter()
{
	Scene::onEnter();

	// load scene data and attach to the root node
	auto creditsScene = CSLoader::createNode( "Credits.csb" );
	addChild( creditsScene );

	// set up event listeners
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2( CreditsScene::onKeyboardEvent, this );

	// add events - they'll be removed when the node is destroyed
	getEventDispatcher()->addEventListenerWithSceneGraphPriority( listener, this );
}


/// <summary>
/// If the player presses any key, will return them to the main menu.
/// </summary>
/// <param name="keyCode">key that was pressed</param>
/// <param name="event">reference to event</param>
void CreditsScene::onKeyboardEvent( EventKeyboard::KeyCode keyCode, Event* event )
{
	SceneService::getInstance()->switchToScene( SceneService::Scenes::StartMenu );
}