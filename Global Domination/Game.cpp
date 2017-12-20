#include <algorithm>
#include <string>

#include "SDL.h"
#include "SDL_ttf.h"

#include "Game.h"
#include "Action.h"
#include "SDL_TextRenderer.h"

namespace global_domination {

	Game::Game()
	{
		ui_ = std::make_unique<GameUserInterface>();
	}

	Game::~Game()
	{
	}

	std::shared_ptr<GameModel> Game::getGameModel()
	{
		return game_model_;
	}

	void Game::initialize()
	{
		game_model_ = std::make_shared<GameModel>();
		ui_->initialize(this);
		ui_->respondToAction(TYPES::ACTION_LIST::CHANGEVIEW_MENU);
	}

	void Game::relayAction(TYPES::ACTION_LIST action)
	{
		if (action == TYPES::ACTION_LIST::QUIT)
		{
			SDL_Event quit_event;
			quit_event.type = SDL_QUIT;
			SDL_PushEvent(&quit_event);
		}

		game_model_->respondToAction(action);
		ui_->respondToAction(action);
	}

	void Game::runGameLoop()
	{
		while (!ui_->isQuiting())
		{
			ui_->update();
			ui_->render();
		}
	}
}