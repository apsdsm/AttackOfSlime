// cocos2d
#include "cocos2d.h"

// classes
#include "SceneService.h"

// scenes
#include "scenes/StartMenuScene.h"
#include "scenes/CreditsScene.h"
#include "scenes/InstructionsScene.h"
#include "scenes/GameScene.h"
#include "scenes/GameOverScene.h"

// using namespaces
using namespace cocos2d;
using namespace AttackOfSlime;

// static global variable //
static SceneService* __instanceSceneService = nullptr;


/// <summary>
/// Returns an instance of the scene manager singleton
/// </summary>
/// <returns>Scene manager singleton</returns>
SceneService* SceneService::getInstance()
{
	if ( !__instanceSceneService )
	{
		__instanceSceneService = new SceneService();
		__instanceSceneService->initialize();
	}

	return __instanceSceneService;
}


/// <summary>
/// Initialize the scene manager
/// </summary>
void SceneService::initialize()
{
	director = Director::getInstance();
}


/// <summary>
/// Set as first scene that is displayed in game.
/// </summary>
/// <param name="newScene">new scene name</param>
void SceneService::runWithScene( SceneService::Scenes newScene )
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
void SceneService::switchToScene( SceneService::Scenes newScene )
{
	if ( newScene == Scenes::Game )
	{
		director->replaceScene( GameScene::create() );
	}
	else if ( newScene == Scenes::GameOver )
	{
		director->replaceScene( GameOverScene::create() );
	}
	else if ( newScene == Scenes::StartMenu )
	{
		director->replaceScene( StartMenuScene::create() );
	}
	else if ( newScene == Scenes::Credits )
	{
		director->replaceScene( CreditsScene::create() );
	}
	else if ( newScene == Scenes::Instructions )
	{
		director->replaceScene( InstructionsScene::create() );
	}
}
