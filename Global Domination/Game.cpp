#include <algorithm>
#include <string>

#include "SDL.h"
#include "SDL_ttf.h"

#include "Game.h"
#include "MenuAction.h"
#include "SDL_TextRenderer.h"

namespace global_domination {

	Game::Game()
	{
		current_action_ = TYPES::ACTION_LIST::MENU;

		nations_.push_back(Nation("Australia"));
		nations_.push_back(Nation("Germany"));
		nations_.push_back(Nation("Japan"));
		nations_.push_back(Nation("USA"));
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
			selected_nation_ = std::make_unique<Nation>(nation_selection_menu_->selectedItem());
			current_action_ = TYPES::ACTION_LIST::START_GAME;
		}

		return 0;
	}

	void Game::handleGameEvent(SDL_Event e)
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
				nation_selection_menu_->handleClick(e.button.x, e.button.y);
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
				main_menu_->handleClick(e.button.x, e.button.y);
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
		initializeNationSelectionMenu();
	}

	void Game::initializeMainMenu()
	{
		SDL_Rect client_area = getClientArea();
		main_menu_ = std::make_unique<SDLMenu<int>>(window_, client_area);
		main_menu_->addMenuItem(MenuItem<int>("PLAY!", std::make_shared<StartGameAction>(this), 0));
		main_menu_->addMenuItem(MenuItem<int>("QUIT!", std::make_shared<QuitGameAction>(this), 1));
	}

	void Game::initializeNationSelectionMenu()
	{
		SDL_Rect client_area = getClientArea();
		nation_selection_menu_ = std::make_unique<SDLMenu<Nation>>(window_, client_area);

		float text_Location_y = 0.05f;
		for (std::vector<Nation>::const_iterator nation = nations_.cbegin(); nation != nations_.end(); nation++)
		{
			SDL_Rect textLocation = { (int)(client_area.w * 0.45), (int)(client_area.h * text_Location_y), 0, 0 };
			std::shared_ptr<NationSelectionAction> nationSelectionAction = std::make_shared<NationSelectionAction>(this);
			std::string nationName = nation->reportString();
			nation_selection_menu_->addMenuItem(MenuItem<Nation>(nationName, nationSelectionAction, *nation));
			text_Location_y += 0.1f;
		}
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
		switch (current_action_)
		{
		case TYPES::ACTION_LIST::MENU:
		{
			main_menu_->renderMenu(renderer_);
		}
		break;
		case TYPES::ACTION_LIST::START_GAME:
		{
			renderGame();
		}
		break;
		}
	}

	void Game::renderGame()
	{
		SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 0xFF);
		SDL_RenderClear(renderer_);

		SDL_Rect client_area = getClientArea();
		SDL_Rect textLocationTitle = { (int)(client_area.w * 0.25), (int)(client_area.h * 0.05), 0, 0 };
		text_renderer::renderText(window_, "GLOBAL DOMINATION!", textLocationTitle, { 0, 255, 0 });

		SDL_Rect textLocationSelectNation = { (int)(client_area.w * 0.15), (int)(client_area.h * 0.25), 0, 0 };
		text_renderer::renderText(window_, "Select a nation:", textLocationSelectNation, { 0, 255, 0 });

		nation_selection_menu_->renderMenu(renderer_);

		SDL_UpdateWindowSurface(window_);
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
			case TYPES::ACTION_LIST::START_GAME:
			{
				handleGameEvent(e);
			}
			break;
			}
		}
	}
}