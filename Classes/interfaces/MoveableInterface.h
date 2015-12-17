#pragma once

// cocos2d
#include "cocos2d.h"

// using namespaces
using namespace cocos2d;

namespace AttackOfSlime
{

	/// <summary>
	/// Classes that implement this interface can be moved somewhere in the scene
	/// specified by a Vec2 coord.
	/// </summary>
	class MoveableInterface
	{
	public:
		virtual void moveToPosition( Vec2 position ) = 0;
	};
}
