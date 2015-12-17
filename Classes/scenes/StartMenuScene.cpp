// scenes
#include "StartMenuScene.h"

// layers
#include "layers/StartMenuLayer.h"

// cocos2d
#include "cocos2d.h"

// using namespaces
using namespace cocos2d;
using namespace AttackOfSlime;

/// <summary>
/// Creates and returns a new start menu scene.
/// </summary>
/// <returns>reference to newly created scene</returns>
Scene* StartMenuScene::create()
{
	auto scene = Scene::create();

	auto startMenuLayer = StartMenuLayer::create();

	scene->addChild( startMenuLayer );

	return scene;
}
