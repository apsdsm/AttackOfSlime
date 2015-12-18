// classes
#include "ScoreManager.h"

// using namespaces
using namespace AttackOfSlime;

// static global variable //
static ScoreManager* __instanceScoreManager = nullptr;


/// <summary>
/// Returns an instance of the score manager singleton.
/// </summary>
/// <returns>Score manager instance reference.</returns>
ScoreManager* ScoreManager::getInstance()
{
	if ( !__instanceScoreManager )
	{
		__instanceScoreManager = new ScoreManager();
	}

	return __instanceScoreManager;
}


/// <summary>
/// Add points to the score.
/// </summary>
/// <param name="points">Number of points to add to the score.</param>
void ScoreManager::addPointsToScore( int points )
{
	score += points;
}


/// <summary>
/// Get the current score.
/// </summary>
/// <returns>tThe current score.</returns>
int ScoreManager::getScore()
{
	return score;
}


/// <summary>
/// Resets the current score to zero.
/// </summary>
void ScoreManager::resetScore()
{
	score = 0;
}