#include <algorithm>
#include <string>

#include "SDL.h"
#include "SDL_ttf.h"

#include "Game.h"
#include "Action.h"
#include "SDL_TextRenderer.h"

#include "InboxView.h"
#include "MainMenuView.h"
#include "NationSelectionView.h"

namespace global_domination {

	Game::Game()
	{
		current_action_ = TYPES::ACTION_LIST::MENU;
	}

	Game::~Game()
	{
	}

	SDL_Rect Game::getClientArea() const
	{
		SDL_Rect client_area;
		SDL_RenderGetViewport(renderer_, &client_area);
		return client_area;
	}

	int Game::getResult()
	{
		if (current_action_ == TYPES::ACTION_LIST::NATION_SELECTION)
		{
			current_action_ = TYPES::ACTION_LIST::NATION_SELECTION;
		}

		return 0;
	}

	void Game::handleNationSelectionEvent(SDL_Event e)
	{
		if (e.type == SDL_KEYDOWN)
		{
			if (e.key.keysym.sym == SDLK_DOWN)
			{
				nation_selection_menu_->nextMenuItem();
			}
			else if (e.key.keysym.sym == SDLK_UP)
			{
				nation_selection_menu_->previousMenuItem();
			}
			else if (e.key.keysym.sym == SDLK_RETURN)
			{
				nation_selection_menu_->selectCurrentItem();
			}
		}
		else if (e.type == SDL_MOUSEBUTTONDOWN)
		{
			if (e.button.button == SDL_BUTTON_LEFT)
			{
				active_view_->handleClick(e.button.x, e.button.y);

			}
		}
	}

	void Game::handleInboxEvent(SDL_Event e)
	{
		if (e.type == SDL_KEYDOWN)
		{
			if (e.key.keysym.sym == SDLK_DOWN)
			{
				nation_selection_menu_->nextMenuItem();
			}
			else if (e.key.keysym.sym == SDLK_UP)
			{
				nation_selection_menu_->previousMenuItem();
			}
			else if (e.key.keysym.sym == SDLK_RETURN)
			{
				nation_selection_menu_->selectCurrentItem();
			}
		}
		else if (e.type == SDL_MOUSEBUTTONDOWN)
		{
			if (e.button.button == SDL_BUTTON_LEFT)
			{
				active_view_->handleClick(e.button.x, e.button.y);

			}
		}
	}

	void Game::handleMenuEvent(SDL_Event e)
	{
		if (e.type == SDL_KEYDOWN)
		{
			if (e.key.keysym.sym == SDLK_DOWN)
			{
				main_menu_->nextMenuItem();
			}
			else if (e.key.keysym.sym == SDLK_UP)
			{
				main_menu_->previousMenuItem();
			}
			else if (e.key.keysym.sym == SDLK_RETURN)
			{
				main_menu_->selectCurrentItem();
			}
		}
		else if (e.type == SDL_MOUSEBUTTONDOWN)
		{
			if (e.button.button == SDL_BUTTON_LEFT)
			{
				active_view_->handleClick(e.button.x, e.button.y);
			}
		}
	}

	void Game::initialize()
	{
		SDL_Surface *surface;

		/* Enable standard application logging */
		SDL_LogSetPriority(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO);

		/* Initialize SDL */
		if (SDL_Init(SDL_INIT_VIDEO) != 0) {
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_Init fail : %s\n", SDL_GetError());
			return;
		}

		/* Create window and renderer for given surface */
		window_ = SDL_CreateWindow("Global Domination", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, kWindowWidth, kWindowHeight, 0);
		if (!window_) {
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Window creation fail : %s\n", SDL_GetError());
			return;
		}

		surface = SDL_GetWindowSurface(window_);
		renderer_ = SDL_CreateSoftwareRenderer(surface);
		if (!renderer_) {
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Render creation for surface fail : %s\n", SDL_GetError());
			return;
		}

		/* Clear the rendering surface with the specified color */
		SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 0xFF);
		SDL_RenderClear(renderer_);

		TTF_Init();

		initializeMainMenu();
	}

	void Game::initializeMainMenu()
	{
		std::unique_ptr<MainMenuView> main_menu_view = std::make_unique<MainMenuView>(this, window_, getClientArea());
		main_menu_view->initialize();
		active_view_ = std::move(main_menu_view);
	}

	const int Game::getWindowWidth()
	{
		return kWindowWidth;
	}

	const int Game::getWindowHeight()
	{
		return kWindowHeight;
	}

	void Game::render()
	{
		active_view_->render(renderer_);
	}

	void Game::runGameLoop()
	{
		while (current_action_ != TYPES::ACTION_LIST::QUIT)
		{
			update();
			render();
		}
	}

	void Game::setAction(TYPES::ACTION_LIST action)
	{
		current_action_ = action;
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

			switch (current_action_)
			{
			case TYPES::ACTION_LIST::MENU:
			{
				handleMenuEvent(e);
			}
			break;
			case TYPES::ACTION_LIST::NATION_SELECTION:
			{
				std::unique_ptr<NationSelectionView> nation_selection_view = std::make_unique<NationSelectionView>(this, window_, getClientArea());
				nation_selection_view->initialize();
				active_view_ = std::move(nation_selection_view);

				handleNationSelectionEvent(e);
			}
			break;
			case TYPES::ACTION_LIST::INBOX:
			{
				std::unique_ptr<InboxView> inbox_view = std::make_unique<InboxView>(this, window_, getClientArea());
				inbox_view->initialize();
				active_view_ = std::move(inbox_view);

				handleInboxEvent(e);
			}
			break;
			}
		}
	}
}