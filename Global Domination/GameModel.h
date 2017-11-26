#pragma once
#include <vector>

#include "Action.h"
#include "Nation.h"
#include "Message.h"

namespace global_domination {

	class GameModel
	{
	public:
		GameModel();
		Nation getSelectedNation();
		std::string getSelectedNationName();
		std::vector<Message> getInboxMessages();
		void nextTurn();
		void respondToAction(TYPES::ACTION_LIST action);
		void setSelectedNation(Nation selected_nation);
		void updateMessages();
		void updateNations();
	private:
		unsigned int current_turn_;
		Nation selected_nation_;
		std::vector<Nation> nations_;
		std::vector<Message> inbox_messages_;
	};
}