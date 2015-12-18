#pragma once
#include "cocos2d.h"

// using namespaces
using namespace cocos2d;

namespace AttackOfSlime
{
	/// <summary>
	/// The first scene in the game. The player can start a new game, or go to a credits
	/// page that has information about the resources used in the game.
	/// </summary>
	class StartMenuScene : public Scene
	{
	public:

		// create and return start menu scene
		CREATE_FUNC( StartMenuScene );

		// called when scene enters the stage
		virtual void onEnter() override;

	private:

		// handle keyboard events
		void onKeyboardEvent( EventKeyboard::KeyCode keyCode, Event* evnet );
	};
}