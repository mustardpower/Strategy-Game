#pragma once

#include <array>
#include <memory>
#include <string>

#include "SDL.h"

#include "GameModel.h"
#include "GameUserInterface.h"
#include "MenuItem.h"
#include "Nation.h"
#include "SDLButton.h"
#include "SDLMenu.h"

namespace global_domination {

	class Game : public IReciever
	{
	public:
		Game();
		~Game();
		std::shared_ptr<GameModel> getGameModel();
		void initialize();
		void relayAction(TYPES::ACTION_LIST action);
		void render();
		void runGameLoop();
		void update();

	private:
		std::unique_ptr<GameUserInterface> ui_;
		std::shared_ptr<GameModel> game_model_;
		TYPES::ACTION_LIST current_action_;
	};

}