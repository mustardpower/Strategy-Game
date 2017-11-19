#include "GameModel.h"

#include <sstream>

namespace global_domination {
	GameModel::GameModel()
	{
		current_turn_ = 0;
	}

	void GameModel::nextTurn()
	{
		current_turn_++;

		updateMessages();
		updateNations();
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

	std::vector<Message> GameModel::getInboxMessages()
	{
		return inbox_messages_;
	}

	void GameModel::setSelectedNation(Nation selected_nation)
	{
		selected_nation_ = selected_nation;
	}

	void GameModel::updateMessages()
	{
		std::stringstream ss;
		ss << current_turn_;
		std::string current_turn_string = ss.str();

		Message aMessage("Turn " + current_turn_string, "Welcome to turn: " + current_turn_string);
		inbox_messages_.push_back(aMessage);
	}

	void GameModel::updateNations()
	{
		for (std::vector<Nation>::iterator nation = nations_.begin(); nation != nations_.end(); nation++)
		{
			nation->update();
		}
	}
}