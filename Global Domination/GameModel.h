#pragma once

#include "SDL.h"

#include <vector>

#include "Action.h"
#include "Nation.h"
#include "Message.h"

namespace global_domination {

	class GameModel
	{
	public:
		GameModel();
		~GameModel();
		std::string getDateString();
		Nation* getNation(std::string name);
		std::vector<Nation*> getNations();
		std::vector<std::string> getPreviousMonthNames(int number_of_months) const;
		Nation* getSelectedNation() const;
		std::string getSelectedNationName();
		std::string getSummaryReport();
		std::vector<Message> getInboxMessages();
		bool isGameFinished() const;
		void nextTurn();
		void pushMessage(Message new_message);
		void respondToAction(Sint32 action);
		void setNations(std::vector<Nation*> nations);
		void setNationalRelationships();
		void setNumberOfTurns(int number_of_turns);
		void setRelationshipsFromJSON(nlohmann::json& j, Nation& nation);
		void setSelectedNation(Nation* selected_nation);
		void updateNations();
	private:
		unsigned int current_turn_;
		time_t date_;
		bool game_finished_;
		unsigned int max_number_of_turns_;
		Nation* selected_nation_;
		std::vector<Nation*> nations_;
		std::vector<Message> inbox_messages_;
	};
}