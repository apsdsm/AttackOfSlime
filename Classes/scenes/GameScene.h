#pragma once
#include "cocos2d.h"

// using namespaces
using namespace cocos2d;

namespace AttackOfSlime
{
	/// <summary>
	/// The main game scene. Player can move around and attack slimes. When player
	/// health drops to zero, will switch to the game over scene.
	/// </summary>
	class GameScene
	{
	public:
	
		// compose and return a game scene
		static Scene* create();
	};
}