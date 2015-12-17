// scenes
#include "GameScene.h"

// layers
#include "layers/DungeonLayer.h"

// cocos2d
#include "cocos2d.h"

// using namespaces
using namespace cocos2d;
using namespace AttackOfSlime;

/// <summary>
/// Composes and returns a game scene, including all the elements of the scene.
/// </summary>
/// <returns>A Scene reference</returns>
Scene* GameScene::create()
{
	auto scene = Scene::create();

	auto dungeonLayer = DungeonLayer::create();

	scene->addChild( dungeonLayer );

	return scene;
}