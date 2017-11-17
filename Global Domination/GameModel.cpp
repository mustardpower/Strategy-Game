#include "GameModel.h"

namespace global_domination {
	GameModel::GameModel()
	{
		current_turn_ = 0;
	}

	void GameModel::nextTurn()
	{
		updateNations();
		current_turn_++;
	}

	void GameModel::respondToAction(TYPES::ACTION_LIST action)
	{
		switch (action)
		{
			case TYPES::ACTION_LIST::NEXT_TURN:
			{
				nextTurn();
			}
			break;
		}
	}

	void GameModel::updateNations()
	{
		for (std::vector<Nation>::iterator nation = nations_.begin(); nation != nations_.end(); nation++)
		{
			nation->update();
		}
	}
}