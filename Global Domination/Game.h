#pragma once

#include <memory>

#include "GameModel.h"
#include "GameUserInterface.h"

namespace global_domination {

	class Game : public IReciever
	{
	public:
		Game();
		~Game();
		std::shared_ptr<GameModel> getGameModel();
		void initialize();
		void relayAction(TYPES::ACTION_LIST action);
		void runGameLoop();

	private:
		std::unique_ptr<GameUserInterface> ui_;
		std::shared_ptr<GameModel> game_model_;
	};

}