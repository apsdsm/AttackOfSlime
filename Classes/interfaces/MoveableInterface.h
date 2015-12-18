#pragma once

// cocos2d
#include "cocos2d.h"

// using namespaces
using namespace cocos2d;

namespace AttackOfSlime
{
	/// <summary>
	/// Classes that implement this interface should be moveable to a position in the scene
	/// specified in pixels in a Vec2.
	/// </summary>
	class MoveableInterface
	{
	public:
		virtual void moveToPosition( Vec2 position ) = 0;
	};
}
