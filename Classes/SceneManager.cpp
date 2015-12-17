// cocos2d
#include "cocos2d.h"

// classes
#include "SceneManager.h"

// scenes
#include "scenes/StartMenuScene.h"
#include "scenes/GameScene.h"
#include "scenes/GameOverScene.h"

// using namespaces
using namespace cocos2d;
using namespace AttackOfSlime;

// static global variable //
static SceneManager* __instanceSceneManager = nullptr;


/// <summary>
/// Returns an instance of the scene manager singleton
/// </summary>
/// <returns>Scene manager singleton</returns>
SceneManager* SceneManager::getInstance()
{
	if ( !__instanceSceneManager )
	{
		__instanceSceneManager = new SceneManager();
		__instanceSceneManager->initialize();
	}

	return __instanceSceneManager;
}


/// <summary>
/// Initialize the scene manager
/// </summary>
void SceneManager::initialize()
{
	director = Director::getInstance();
}


/// <summary>
/// Set as first scene that is displayed in game.
/// </summary>
/// <param name="newScene">new scene name</param>
void SceneManager::runWithScene( SceneManager::Scenes newScene )
{
	if ( newScene == Scenes::StartMenu )
	{
		director->runWithScene( StartMenuScene::create() );
	}
}


/// <summary>
/// Switches to scene, dumping the old one in the process.
/// </summary>
/// <param name="newScene">new scene name</param>
void SceneManager::switchToScene( SceneManager::Scenes newScene )
{
	if ( newScene == Scenes::Game )
	{
		director->replaceScene( GameScene::create() );
		CCLOG( "added game scene" );
	}
	else if ( newScene == Scenes::GameOver )
	{
		director->replaceScene( GameOverScene::create() );
	}
	else if ( newScene == Scenes::StartMenu )
	{
		director->replaceScene( StartMenuScene::create() );
	}
}
