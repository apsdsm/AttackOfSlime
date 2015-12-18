// classes
#include "ScoreService.h"

// using namespaces
using namespace AttackOfSlime;

// static global variable //
static ScoreService* __instanceScoreService = nullptr;


/// <summary>
/// Returns an instance of the score manager singleton.
/// </summary>
/// <returns>Score manager instance reference.</returns>
ScoreService* ScoreService::getInstance()
{
	if ( !__instanceScoreService )
	{
		__instanceScoreService = new ScoreService();
	}

	return __instanceScoreService;
}


/// <summary>
/// Add points to the score.
/// </summary>
/// <param name="points">Number of points to add to the score.</param>
void ScoreService::addPointsToScore( int points )
{
	score += points;
}


/// <summary>
/// Get the current score.
/// </summary>
/// <returns>tThe current score.</returns>
int ScoreService::getScore()
{
	return score;
}


/// <summary>
/// Resets the current score to zero.
/// </summary>
void ScoreService::resetScore()
{
	score = 0;
}