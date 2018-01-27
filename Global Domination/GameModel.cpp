#define _CRT_SECURE_NO_WARNINGS

#include "GameModel.h"

#include <fstream>
#include <iomanip>
#include <sstream>

#include "PlayerNation.h"

namespace global_domination {
	
	GameModel::GameModel()
	{
		struct tm* time = new tm();
		time->tm_mon = 0;
		time->tm_mday = 1;
		time->tm_year = 118;
		date_ = mktime(time);
		delete time;
		current_turn_ = 0;

		selected_nation_ = nullptr;

	}

	GameModel::~GameModel()
	{
		selected_nation_ = nullptr;
	}

	std::string GameModel::getDateString()
	{
		std::stringstream ss;
		ss << std::put_time(localtime(&date_), "%d %b %Y");
		return ss.str();
	}

	std::vector<Message> GameModel::getInboxMessages()
	{
		return inbox_messages_;
	}

	Nation* GameModel::getNation(std::string name)
	{
		for (std::vector<Nation*>::iterator nation = nations_.begin(); nation != nations_.end(); nation++)
		{
			if ((*nation)->getName() == name)
			{
				return *nation;
			}
		}

		return nullptr;
	}

	std::vector<Nation*> GameModel::getNations()
	{
		return nations_;
	}

	std::vector<std::string> GameModel::getPreviousMonthNames(int number_of_months) const
	{
		std::vector<std::string> month_names;
		struct tm* time = localtime(&date_);
		time->tm_mon -= number_of_months;
		time_t date;

		for (int i = 0; i < number_of_months; i++)
		{
			date = mktime(time);
			std::stringstream ss;
			ss << std::put_time(localtime(&date), "%m/%Y");
			month_names.push_back(ss.str());
			time->tm_mon++;
		}

		return month_names;
	}

	Nation* GameModel::getSelectedNation() const
	{
		return selected_nation_;
	}

	std::string GameModel::getSummaryReport()
	{
		return "Everything is superb!";
	}

	void GameModel::nextTurn()
	{
		struct tm* time = localtime(&date_);
		time->tm_mon += 1;
		date_ = mktime(time);

		Message turn_summary_message("Progress report", getSummaryReport());
		pushMessage(turn_summary_message);

		current_turn_++;

		if (current_turn_ > max_number_of_turns_)
		{
			Message end_of_game_message("The end is here!", "You have won");
			pushMessage(end_of_game_message);
		}
		else
		{
			updateNations();
		}
	}

	void GameModel::pushMessage(Message new_message)
	{
		inbox_messages_.push_back(new_message);
	}

	void GameModel::respondToAction(Sint32 action)
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

	void GameModel::setNations(std::vector<Nation*> nations)
	{
		nations_ = nations;
	}

	void GameModel::setNationalRelationships()
	{
		// go through JSON file
		// if defined in JSON then set the relationship between the nations to the value specified
		// if not defined then set as a neutral relationship
		std::ifstream i("nation relationships.json");

		if (i.is_open())
		{
			nlohmann::json j;
			i >> j;

			for (nlohmann::json::iterator it = j.begin(); it != j.end(); ++it)
			{
				Nation* nation = getNation(it->at("name").get<std::string>());
				setRelationshipsFromJSON(*it, *nation);
			}

			i.close();
		}
	}

	void GameModel::setNumberOfTurns(int number_of_turns)
	{
		max_number_of_turns_ = number_of_turns;
	}

	void GameModel::setRelationshipsFromJSON(nlohmann::json& j, Nation& nation)
	{
		std::map<std::string, double> relations;
		for (nlohmann::json::iterator it = j.begin(); it != j.end(); ++it)
		{
			relations = j.at("relationships").get<std::map<std::string, double>>();
			for (std::map<std::string, double>::iterator pair = relations.begin(); pair != relations.end(); pair++)
			{
				Nation* matching_nation = getNation(pair->first);
				if (matching_nation)
				{
					nation.setRelationship(matching_nation, pair->second);
				}
			}

		}
	}

	std::string GameModel::getSelectedNationName()
	{
		std::string nation_name = selected_nation_->getName();
		if (!nation_name.size())
		{
			return "Undefined Nation";
		}

		return nation_name;
	}

	void GameModel::setSelectedNation(Nation* selected_nation)
	{
		// create a PlayerNation object from the selected nation
		if (selected_nation_) { delete selected_nation_; }
		selected_nation_ = new PlayerNation(*selected_nation, inbox_messages_);

		std::vector<Nation*>::iterator nation = std::find(nations_.begin(), nations_.end(), selected_nation);
		nations_.erase(nation);
		nations_.push_back(selected_nation_);
	}

	void GameModel::updateNations()
	{
		for (std::vector<Nation*>::iterator nation = nations_.begin(); nation != nations_.end(); nation++)
		{
			(*nation)->update(date_);
		}
	}
}