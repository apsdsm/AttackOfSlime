#pragma once

// cocos2d
#include "cocos2d.h"

// namespaces
using namespace cocos2d;

namespace AttackOfSlime {

	/// <summary>
	/// The scene manager passes requests to change scenes to the Director, and helps to
	/// reduce the amount of information scenes need to know about each other.
	/// </summary>
	class SceneService
	{
	public:

		enum Scenes {
			StartMenu,
			Game,
			GameOver,
			Credits,
			Instructions
		};

		// static method returns instance to singleton manager
		static SceneService* getInstance();

		// invokes the current scene as the starting scene
		void runWithScene( Scenes newScene );

		// dump the current scene and switch to this one
		void switchToScene( Scenes newScene );

	private:

		// reference to the director
		Director* director;

		// initialize after creation
		void initialize();
	};
}
