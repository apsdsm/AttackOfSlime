#pragma once

// cocos2s
#include "cocos2d.h"
#include "SimpleAudioEngine.h"

// interfaces
#include "interfaces/MoveableInterface.h"
#include "interfaces/DamagableInterface.h"

// enumerations
#include "enumerations/Direction.h"

// using namespaces
using namespace cocos2d;
using namespace CocosDenshion;

namespace AttackOfSlime
{
	// forward declarations
	class Dungeon;
	class ScoreService;


	/// <summary>
	/// The player controlled avatar is able to move around the dungeon and 
	/// attack slimes by bashing into them. If slimes attack the player, health
	/// is reduced. If health reaches zero, the game ends.
	/// </summary>
	class Player : public Sprite, public MoveableInterface, public DamagableInterface
	{
	public:

		// creates a new player object
		static Player* create( Dungeon* dungeon );

		// init the player object
		void initOptions( Dungeon* dungeon );

		// called when sprite enters the stage
		virtual void onEnter() override;

		// update player each frame
		virtual void update( float delta ) override;

		// MoveableInferface : move the player to a new position
		void moveToPosition( cocos2d::Vec2 position );

		// DamagableInterface : damage the player by a given amount
		void damage( int damageAmmount );

		// get the player's current health
		int getHealth();

	private:

		// how much damage the player deals
		int attackStrength = 10;

		// how much damage the player can take
		int health = 100;

		// the dungeon this player exists in
		Dungeon* dungeon;

		// cached reference to the audio engine
		SimpleAudioEngine* audio;

		// time between actions
		float actionCooldown = 0.05f;

		// time since last action
		float timeSinceAction = 0.0f;

		// true if the player is currently being damaged
		bool receivingDamage = false;

		// maps which keys correspond to which directions
		static std::map<EventKeyboard::KeyCode, Direction> keyMap;

		// event listener for keyboard events
		EventListenerKeyboard* keyboardEventListener;

		// triggered when a key is pressed
		void onKeyboardEvent( cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* event );
	};
}
