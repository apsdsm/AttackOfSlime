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
	/// Slimes explore the dungeon, looking for the player. If they are next to the player, 
	/// they will attack. If they take damage, they will be stunned for a fraction of a 
	/// second, and won't be able to do anything.
	/// </summary>
	class Slime : public Sprite, public MoveableInterface, public DamagableInterface
	{
	public:

		// create a new slime
		static Slime* create( SlimeManager* factory );

		// called every frame
		virtual void update( float deltaTime ) override;

		// move slime to position
		void moveToPosition( Vec2 position );

		// damage slime by amount
		void damage( int amount );

		// get the score modifier for the slime
		int getScoreModifier();

	private:

		// used when calculating cost of next move
		struct PotentialMove 
		{
			DungeonTile* tile;
			float cost;
		};

		// manager that controls this slime
		SlimeManager* manager;

		// audio engine used by this slime
		SimpleAudioEngine* audio;

		// how much the score is modified when slime is killed
		int scoreModifier = 100;

		// time between actions
		float actionCooldown = 1.0f;

		// time since last action
		float timeSinceAction = 0.0f;

		// how much damage slime imparts
		int attackStrength = 10;

		// how much damage slime can take
		int health = 20;

		// true if the slime is currently being damaged
		bool receivingDamage = false;

		// hot long it takes for the slime to recover after being hit
		float recoveryCooldown = 0.2f;

		// time left until slime has recovered
		float timeToRecovery = 0.0f;

		// memory of recent past moves
		std::vector<DungeonTile*> moveHistory;

		// initializes the slime
		void initOptions( SlimeManager* manager );
	};
}
