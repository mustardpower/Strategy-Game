#pragma once
#include "Action.h"

namespace global_domination {

	class GameModel
	{
	public:
		GameModel();
		void nextTurn();
		void respondToAction(TYPES::ACTION_LIST action);
	private:
		unsigned int current_turn;
	};
}