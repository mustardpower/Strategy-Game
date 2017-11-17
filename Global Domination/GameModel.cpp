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

	std::string GameModel::getSelectedNationName()
	{
		std::string nation_name = selected_nation_.getName();
		if (!nation_name.size())
		{
			return "Undefined Nation";
		}

		return nation_name;
	}

	void GameModel::setSelectedNation(Nation selected_nation)
	{
		selected_nation_ = selected_nation;
	}

	void GameModel::updateNations()
	{
		for (std::vector<Nation>::iterator nation = nations_.begin(); nation != nations_.end(); nation++)
		{
			nation->update();
		}
	}
}