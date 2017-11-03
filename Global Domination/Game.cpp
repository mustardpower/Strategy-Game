#include <algorithm>
#include <string>

#include "SDL.h"
#include "SDL_ttf.h"

#include "Game.h"
#include "Action.h"
#include "SDL_TextRenderer.h"

#include "MainMenuView.h"

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
				nation_selection_menu_->handleClick(e.button.x, e.button.y);
				start_button_->handleClick(e.button.x, e.button.y);

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
				nation_selection_menu_->handleClick(e.button.x, e.button.y);
				start_button_->handleClick(e.button.x, e.button.y);

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

		initializeStartButton();
		initializeMainMenu();
		initializeNationSelectionMenu();
	}

	void Game::initializeStartButton()
	{
		SDL_Rect client_area = getClientArea();
		start_button_ = std::make_unique<SDLButton>(window_, "START", std::make_shared<OpenInboxAction>(this), client_area.w * 0.8, client_area.h * 0.8, 200, 300);
	}

	void Game::initializeMainMenu()
	{
		std::unique_ptr<MainMenuView> main_menu_view = std::make_unique<MainMenuView>(this, window_, getClientArea());
		main_menu_view->initialize();
		active_view_ = std::move(main_menu_view);
	}

	void Game::initializeNationSelectionMenu()
	{
		SDL_Rect client_area = getClientArea();
		nation_selection_menu_ = std::make_unique<SDLMenu<Nation>>(window_, client_area.w * 0.2, client_area.h * 0.4, client_area.h * 0.1);

		for (std::vector<Nation>::const_iterator nation = nations_.cbegin(); nation != nations_.end(); nation++)
		{
			std::shared_ptr<NationSelectionAction> nationSelectionAction = std::make_shared<NationSelectionAction>(this);
			std::string nationName = nation->reportString();
			nation_selection_menu_->addMenuItem(MenuItem<Nation>(nationName, nationSelectionAction, *nation));
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
			active_view_->render(renderer_);
		}
		break;
		case TYPES::ACTION_LIST::NATION_SELECTION:
		{
			renderNationSelection();
		}
		break;
		case TYPES::ACTION_LIST::INBOX:
		{
			renderInbox();
		}
		break;
		}
	}

	void Game::renderInbox()
	{
		SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 0xFF);
		SDL_RenderClear(renderer_);

		SDL_Rect client_area = getClientArea();
		SDL_Rect textLocationTitle = { (int)(client_area.w * 0.25), (int)(client_area.h * 0.05), 0, 0 };
		text_renderer::renderText(window_, "INBOX", textLocationTitle, { 0, 255, 0 });

		SDL_UpdateWindowSurface(window_);
	}

	void Game::renderNationSelection()
	{
		SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 0xFF);
		SDL_RenderClear(renderer_);

		SDL_Rect client_area = getClientArea();
		SDL_Rect textLocationTitle = { (int)(client_area.w * 0.25), (int)(client_area.h * 0.05), 0, 0 };
		text_renderer::renderText(window_, "GLOBAL DOMINATION!", textLocationTitle, { 0, 255, 0 });

		SDL_Rect textLocationSelectNation = { (int)(client_area.w * 0.15), (int)(client_area.h * 0.25), 0, 0 };
		text_renderer::renderText(window_, "Select a nation:", textLocationSelectNation, { 0, 255, 0 });

		nation_selection_menu_->render(renderer_);

		start_button_->render(renderer_);

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
			case TYPES::ACTION_LIST::NATION_SELECTION:
			{
				handleNationSelectionEvent(e);
			}
			break;
			case TYPES::ACTION_LIST::INBOX:
			{
				handleInboxEvent(e);
			}
			break;
			}
		}
	}
}