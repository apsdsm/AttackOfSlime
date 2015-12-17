#pragma once

// cocos2d
#include "cocos2d.h"

namespace AttackOfSlime {

	/// <summary>
	/// Passes requests to change scenes to the Director object.
	/// </summary>
	class SceneManager
	{
	public:

		enum Scenes {
			StartMenu,
			Game,
			GameOver
		};

		// static method returns instance to singleton manager
		static SceneManager* getInstance();

		// invokes the current scene as the starting scene
		void runWithScene( Scenes newScene );

		// dump the current scene and switch to this one
		void switchToScene( Scenes newScene );

	private:

		cocos2d::Director* director;

		// initialize after creation
		void initialize();
	};
}
