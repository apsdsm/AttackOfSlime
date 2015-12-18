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
	class CreditsScene : public Scene
	{
	public:

		// compose and return a game scene
		CREATE_FUNC( CreditsScene );

		// called when scene enters the stage
		virtual void onEnter() override;

	private:

		// handle keyboard events
		void onKeyboardEvent( EventKeyboard::KeyCode keyCode, Event* event );
	};
}