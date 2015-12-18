#pragma once

namespace AttackOfSlime
{
	/// <summary>
	/// The score manager keeps track of the current score between scenes.
	/// </summary>
	class ScoreService
	{
	public:

		// get an instance of the singleton manager
		static ScoreService* getInstance();

		// add the specified number of points to the score
		void addPointsToScore( int points );

		// get the current score
		int getScore();

		// reset the current score to zero
		void resetScore();

	private:

		// current player score
		int score = 0;

	};
}