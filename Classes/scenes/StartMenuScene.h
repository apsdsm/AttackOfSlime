#pragma once
#include "cocos2d.h"

// using namespaces
using namespace cocos2d;

namespace AttackOfSlime
{
	/// <summary>
	/// The first screen in the game. The player can press space to start playing
	/// or 'c' to view a screen of credits.
	/// </summary>
	class StartMenuScene
	{
	public:

		// create and return start menu scene
		static Scene* create();
	};
}