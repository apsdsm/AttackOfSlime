#pragma once

// cocos2d
#include "cocos2d.h"

// using namespaces
using namespace cocos2d;

namespace AttackOfSlime
{
	class StartMenuLayer : public Layer
	{
	public:

		// generated create method
		CREATE_FUNC( StartMenuLayer );

		// init the class
		virtual bool init();

		// layer enters the stage
		virtual void onEnter();

		// layer leaves the stage
		virtual void onExit();

	private:

		// event listener for keyboard events
		EventListenerKeyboard* keyboardEventListener;

		// handle keyboard events
		void onKeyboardEvent( EventKeyboard::KeyCode keyCode, Event* event );

	};
}
