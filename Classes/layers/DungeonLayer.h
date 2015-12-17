#pragma once

// cocos2d
#include "cocos2d.h"

// using namespaces
using namespace cocos2d;

namespace AttackOfSlime
{
	class DungeonLayer : public Layer
	{
	public:

		CREATE_FUNC( DungeonLayer );

		virtual bool init();

		virtual void onEnter();

		virtual void onExit();

	private:

		// event listener for keyboard events
		EventListenerKeyboard* keyboardEventListener;

		// handle keyboard events
		void onKeyboardEvent( EventKeyboard::KeyCode keyCode, Event* event );

	};
}