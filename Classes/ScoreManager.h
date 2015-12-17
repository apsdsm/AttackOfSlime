#pragma once

namespace AttackOfSlime
{
	/// <summary>
	/// Keeps track of the current player score.
	/// </summary>
	class ScoreManager
	{
	public:

		// get an instance of the singleton manager
		static ScoreManager* getInstance();

		// add the specified number of points to the score
		void addPointsToScore( int points );

		// get the current score
		int getScore();

	private:

		// current player score
		int score = 0;

	};
}