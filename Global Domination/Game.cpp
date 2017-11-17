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
		current_action_ = TYPES::ACTION_LIST::UNINITIALIZED;
		ui_ = std::make_unique<GameUserInterface>();
	}

	Game::~Game()
	{
	}

	void Game::initialize()
	{
		ui_->initialize(this);

		game_model_ = std::make_shared<GameModel>();

		ui_->respondToAction(TYPES::ACTION_LIST::CHANGEVIEW_MENU);
	}

	void Game::relayAction(TYPES::ACTION_LIST action)
	{
		ui_->respondToAction(action);
	}

	void Game::render()
	{
		ui_->render();
	}

	void Game::runGameLoop()
	{
		while (current_action_ != TYPES::ACTION_LIST::QUIT)
		{
			update();
			render();
		}
	}

	void Game::update()
	{
		SDL_Event e;

		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				current_action_ = TYPES::ACTION_LIST::QUIT;
				return;
			}

			if ((e.type == SDL_KEYDOWN) && (e.key.keysym.sym == SDLK_ESCAPE)) {
				current_action_ = TYPES::ACTION_LIST::QUIT;
				return;
			}

			if (e.type == SDL_KEYDOWN)
			{
				if (e.key.keysym.sym == SDLK_DOWN)
				{
					ui_->respondToAction(TYPES::ACTION_LIST::KEYPRESS_DOWN);
				}
				else if (e.key.keysym.sym == SDLK_UP)
				{
					ui_->respondToAction(TYPES::ACTION_LIST::KEYPRESS_UP);
				}
				else if (e.key.keysym.sym == SDLK_RETURN)
				{
					ui_->respondToAction(TYPES::ACTION_LIST::KEYPRESS_RETURN);
				}
			}
			else if (e.type == SDL_MOUSEBUTTONDOWN)
			{
				if (e.button.button == SDL_BUTTON_LEFT)
				{
					ui_->respondToMouseClick(TYPES::ACTION_LIST::MOUSECLICK_LEFT, e.button.x, e.button.y);

				}
			}
		}
	}
}