#pragma once

namespace AttackOfSlime {

	/// <summary>
	/// Classes that implement this interface should be damageable.
	/// </summary>
	class DamagableInterface
	{
	public:
		virtual void damage( int damageAmmount ) = 0;
	};
}

