#include "GameModel.h"

namespace global_domination {
	GameModel::GameModel()
	{
		current_turn = 0;
	}

	void GameModel::nextTurn()
	{
		current_turn++;
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
}