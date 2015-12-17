#pragma once

// cocos2d
#include "cocos2d.h"

// using namespaces
using namespace cocos2d;

namespace AttackOfSlime
{
	/// <summary>
	/// Displayed when the player health drops to zero. From this screen the 
	/// player can press space to return to the main menu.
	/// </summary>
	class GameOverScene
	{
	public:

		// compose and return a game scene
		static Scene* create();
	};
}