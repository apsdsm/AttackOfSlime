// scenes
#include "GameOverScene.h"

// layers
#include "layers/GameOverLayer.h"

// cocos2d
#include "cocos2d.h"

// using namespaces
using namespace cocos2d;
using namespace AttackOfSlime;

/// <summary>
/// Composes and returns a game scene, including all the elements of the scene.
/// </summary>
/// <returns>A Scene reference</returns>
Scene* GameOverScene::create()
{
	auto scene = Scene::create();

	auto gameOverLayer = GameOverLayer::create();

	scene->addChild( gameOverLayer );

	return scene;
}