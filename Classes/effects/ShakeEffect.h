#pragma once

// cocos2d
#include "2d\CCActionInterval.h"

using namespace cocos2d;

namespace AttackOfSlime {

	/// <summary>
	/// Shakes the target node briefly.
	/// </summary>
	class ShakeEffect : public ActionInterval
	{
	public:

		// static generator that returns a useable shake effect
		static ShakeEffect* withDuration( float duration );

		// override : called when effect starts
		virtual void startWithTarget( Node* target );

		// override : called once per frame
		virtual void update( float delta );

		// override : called when effect stops
		virtual void stop();

	protected:

		// override : initializes effect with a set duration 
		virtual bool initWithDuration( float duration );

		// starting x coord of target
		int startX;

		// starting y coord of target
		int startY;
	};
}
