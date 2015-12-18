// classes
#include "ShakeEffect.h"

// using namespaces
using namespace AttackOfSlime;


/// <summary>
/// Static generator method. Creates effect with specified duration.
/// </summary>
/// <param name="duration">how long to shake</param>
/// <returns>An action interval that can be run by a node</returns>
ShakeEffect* ShakeEffect::withDuration( float duration )
{
	auto shakeEffect = new ShakeEffect();

	shakeEffect->initWithDuration( duration );
	shakeEffect->autorelease();

	return shakeEffect;
}


/// <summary>
/// Initializes the action interval.
/// </summary>
/// <param name="duration">how long to shake</param>
/// <returns>true if successful</returns>
bool ShakeEffect::initWithDuration( float duration )
{
	if ( !ActionInterval::initWithDuration( duration ) )
	{
		return false;
	}
}


/// <summary>
/// Called once per frame
/// </summary>
/// <param name="delta">how much time has passed</param>
void ShakeEffect::update( float delta )
{
	int shakeX = ( std::rand() % 4 ) - 2;
	int shakeY = ( std::rand() % 4 ) - 2;

	_target->setPosition( Vec2( startX + shakeX, startY + shakeY ) );
}


/// <summary>
/// Called when action interval starts.
/// </summary>
/// <param name="target">target of effect</param>
void ShakeEffect::startWithTarget( Node* target )
{
	ActionInterval::startWithTarget( target );

	// save starting position
	startX = target->getPosition().x;
	startY = target->getPosition().y;
}


/// <summary>
/// Called when action interval stops.
/// </summary>
void ShakeEffect::stop()
{
	_target->setPosition( Vec2( startX, startY ) );

	ActionInterval::stop();
}