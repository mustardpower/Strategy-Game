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
		void updateNations();
	private:
		unsigned int current_turn_;
		std::vector<Nation> nations_;
	};
}