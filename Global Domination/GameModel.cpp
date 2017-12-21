#define _CRT_SECURE_NO_WARNINGS

#include "GameModel.h"

#include <sstream>
#include <iomanip>

namespace global_domination {
	
	GameModel::GameModel()
	{
		struct tm* time = new tm();
		time->tm_mon = 1;
		time->tm_mday = 1;
		time->tm_year = 118;
		date = mktime(time);
		current_turn_ = 0;

	}

	GameModel::~GameModel()
	{
		
	}

	std::string GameModel::getDateString()
	{
		std::stringstream ss;
		ss << std::put_time(localtime(&date), "%d %b %Y");
		return ss.str();
	}

	Nation GameModel::getSelectedNation()
	{
		return selected_nation_;
	}

	std::string GameModel::getSummaryReport()
	{
		return "Everything is superb!";
	}

	void GameModel::nextTurn()
	{
		struct tm* time = localtime(&date);
		time->tm_mday += 1;
		date = mktime(time);

		Message turn_summary_message("Progress report", getSummaryReport());
		pushMessage(turn_summary_message);

		current_turn_++;

		updateNations();
	}

	void GameModel::pushMessage(Message new_message)
	{
		inbox_messages_.push_back(new_message);
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

	void GameModel::updateNations()
	{
		for (std::vector<Nation>::iterator nation = nations_.begin(); nation != nations_.end(); nation++)
		{
			nation->update();
		}
	}
}