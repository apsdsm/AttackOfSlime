#pragma once

// cocos2d
#include "cocos2d.h"

// using namespaces
using namespace cocos2d;

namespace AttackOfSlime
{
	// forward declarations
	class Slime;
	class Dungeon;

	/// <summary>
	/// Is responsible for adding new slimes to the dungeon at a constant rate,
	/// and for removing those slimes from the game when they die.
	/// </summary>
	class SlimeManager : public Node
	{
	public:
		
		CREATE_FUNC( SlimeManager );

		//SlimeManager( Dungeon* dungeon );
		
		// initialize manager when created
		virtual bool init() override;

		// update manager each frame
		virtual void update( float deltaTime ) override;

		// destroys slimes that notify the manager of their death
		void notifyOfDeath( Slime *slime );

	private:

		// list of slimes manager is responsible for
		std::vector<Slime*> slimes;

		// the rate in seconds at which new slimes spawn
		float spawnCooldown = 1.0f;

		// time that has elapsed since the last slime spawned
		float timeSinceSpawn = 1.0f;

		// spawns a new slime
		void spawnNewSlime();
	};
}
