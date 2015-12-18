#pragma once

// cocos2d
#include "cocos2d.h"
#include "ui/CocosGUI.h"

// using namespaces
using namespace cocos2d::ui;

namespace AttackOfSlime
{
	// forward declarations
	class Player;
	class Dungeon;

	/// <summary>
	/// The Game UI makes changes to the user interface during the game scene. Other
	/// components can ask the UI to redraw itself by calling the `setDirty` method.
	/// </summary>
	class GameUI : public cocos2d::Node
	{
	public:

		// create a new game UI
		CREATE_FUNC( GameUI );
	
		// called every frame
		virtual void update( float deltaTime ) override;

		// called when UI enters stage
		virtual void onEnter() override;

		// tells the UI to refresh next chance it gets
		void setDirty();

	private:

		// Text label for player's score
		Text* score;

		// Text label for the player's health
		Text* health;

		// if true, UI will update
		bool dirty = false;

		// updates score label in UI
		void updateScore();

		// updates health label in UI
		void updateHealth();
	};
}