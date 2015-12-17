#pragma once

// cocos2d
#include "cocos2d.h"
#include "SimpleAudioEngine.h"

// interfaces
#include "interfaces/MoveableInterface.h"
#include "interfaces/DamagableInterface.h"

// structures
#include "DungeonTile.h"

// namespaces
using namespace cocos2d;
using namespace CocosDenshion;

namespace AttackOfSlime
{
	// forward declarations
	class Dungeon;
	class DungeonTile;
	class SlimeManager;

	/// <summary>
	/// Explores dungeon looking for the player. When next to the player will attack.
	/// </summary>
	class Slime : public Sprite, public MoveableInterface, public DamagableInterface
	{
	public:

		// create a new slime
		static Slime* create( Dungeon* dungeon, SlimeManager* factory );

		// implement Updateable
		virtual void update( float deltaTime );

		// implement Moveable
		void moveToPosition( Vec2 position );

		// implement Damageable
		void damage( int ammount );

		// how much is this slime worth?
		int getScoreModifier();

	private:

		// used when calculating cost of next move
		struct PotentialMove {
			DungeonTile* tile;
			float cost;
		};

		// dungeon this slime belongs in
		//Dungeon* dungeon;

		// manager that controls this slime
		SlimeManager* manager;

		// audio engine used by this slime
		SimpleAudioEngine* audio;

		// how much is this slime worth when killed?
		int scoreModifier = 100;

		// time between actions
		float actionCooldown = 1.0f;

		// time since last action
		float timeSinceAction = 0.0f;

		// how much damage slime imparts
		int attackStrength = 10;

		// how much damage slime can take
		int health = 20;

		// is the slime receiving damage right now?
		bool receivingDamage = false;

		// how long does it take the slime to recover after being hit?
		float recoveryCooldown = 0.2f;

		// how long until the slime has recovered?
		float timeToRecovery = 0.0f;

		// memory of recent past moves
		std::vector<DungeonTile*> moveHistory;

		// initialize the slime
		void initialize( Dungeon* dungeon, SlimeManager* manager );
	};
}
