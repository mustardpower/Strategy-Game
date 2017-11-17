#pragma once
#include <vector>

#include "Action.h"
#include "Nation.h"

namespace global_domination {

	class GameModel
	{
	public:
		GameModel();
		void nextTurn();
		void respondToAction(TYPES::ACTION_LIST action);
		std::string getSelectedNationName();
		void setSelectedNation(Nation selected_nation);
		void updateNations();
	private:
		unsigned int current_turn_;
		Nation selected_nation_;
		std::vector<Nation> nations_;
	};
}