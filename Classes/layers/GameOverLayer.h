#pragma once

// cocos2d
#include "cocos2d.h"

// using namespaces
using namespace cocos2d;

namespace AttackOfSlime
{
	class GameOverLayer : public Layer
	{
	public:

		// generated create method
		CREATE_FUNC( GameOverLayer );

		// init the class
		virtual bool init();

		// layer enters the stage
		virtual void onEnter();

		// layer leaves the stage
		virtual void onExit();

	private:

		// handle keyboard events
		void onKeyboardEvent( EventKeyboard::KeyCode keyCode, Event* event );
	};
}
