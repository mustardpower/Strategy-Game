#pragma once

#include "GameModel.h"
#include "GameUserInterface.h"

namespace global_domination {

	class Game
	{
	public:
		Game();
		~Game();
		GameModel& getGameModel();
		void initialize();
		void relayAction(TYPES::ACTION_LIST action);
		void runGameLoop();

	private:
		GameUserInterface ui_;
		GameModel game_model_;
	};

}