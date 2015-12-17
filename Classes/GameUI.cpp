// classes
#include "GameUI.h"
#include "Dungeon.h"
#include "ScoreManager.h"
#include "Player.h"

// services
#include "services/DirectoryService.h"

// using namespaces
using namespace cocos2d;
using namespace cocos2d::ui;
using namespace AttackOfSlime;


/// <summary>
/// Sets up the UI when it enters the stage. gets references to the text labels it uses,
/// sets the update schedule, and registers itself with the node directory.
/// </summary>
void GameUI::onEnter()
{
	Node::onEnter();

	score = getChildByName<Text*>( "Score" );
	health = getChildByName<Text*>( "Health" );

	this->scheduleUpdate();

	DirectoryService::getInstance()->registerNode( "GameUI", this );
}


/// <summary>
/// Sets the dirty flag to true.
/// </summary>
void GameUI::setDirty()
{
	dirty = true;
}


/// <summary>
/// If dirty flag is set, will update UI elements, then unset the dirty flag.
/// </summary>
/// <param name="deltaTime">Time passed since last update.</param>
void GameUI::update( float deltaTime )
{
	if ( dirty )
	{
		updateHealth();
		updateScore();

		dirty = false;
	}
}


/// <summary>
/// Checks the current score with the score manager, then writes that to the UI.
/// </summary>
void GameUI::updateScore()
{
	score->setString( std::to_string( ScoreManager::getInstance()->getScore() ) );
}


/// <summary>
/// Checks the player's current health, then writes that to the UI.
/// </summary>
void GameUI::updateHealth()
{
	Player* player = ( Player* ) DirectoryService::getInstance()->lookUp( "Player" );
	
	health->setString( std::to_string( player->getHealth() ) );
}