#pragma once
#include <chrono>
#include <vector>

#include "Action.h"
#include "Nation.h"
#include "Message.h"

namespace global_domination {

	class GameModel
	{
	public:
		GameModel();
		std::string getDateString();
		Nation getSelectedNation();
		std::string getSelectedNationName();
		std::string getSummaryReport();
		std::vector<Message> getInboxMessages();
		void nextTurn();
		void pushMessage(Message new_message);
		void respondToAction(TYPES::ACTION_LIST action);
		void setSelectedNation(Nation selected_nation);
		void updateNations();
	private:
		unsigned int current_turn_;
		std::chrono::system_clock::time_point date;
		Nation selected_nation_;
		std::vector<Nation> nations_;
		std::vector<Message> inbox_messages_;
	};
}