// classes
#include "ScoreManager.h"

// using namespaces
using namespace AttackOfSlime;

// static global variable //
static ScoreManager* __instanceScoreManager = nullptr;


/// <summary>
/// Returns an instance of the score manager singleton.
/// </summary>
/// <returns>Score manager singleton</returns>
ScoreManager* ScoreManager::getInstance()
{
	if ( !__instanceScoreManager )
	{
		__instanceScoreManager = new ScoreManager();
	}

	return __instanceScoreManager;
}


/// <summary>
/// Add the points to the score.
/// </summary>
/// <param name="points"></param>
void ScoreManager::addPointsToScore( int points )
{
	score += points;
}


/// <summary>
/// Get the current score.
/// </summary>
/// <returns></returns>
int ScoreManager::getScore()
{
	return score;
}
