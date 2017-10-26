#include <algorithm>
#include <string>

#include "SDL.h"
#include "SDL_ttf.h"

#include "Game.h"
#include "MenuAction.h"
#include "SDL_TextRenderer.h"

namespace global_domination {

	const int Game::WINDOW_WIDTH = 640;
	const int Game::WINDOW_HEIGHT = 480;

	Game::Game()
	{
		currentAction = TYPES::ACTION_LIST::MENU;

		nations.push_back(Nation("Australia"));
		nations.push_back(Nation("Germany"));
		nations.push_back(Nation("Japan"));
		nations.push_back(Nation("USA"));
	}

	Game::~Game()
	{
	}

	SDL_Rect Game::getClientArea() const
	{
		SDL_Rect clientArea;
		SDL_RenderGetViewport(renderer, &clientArea);
		return clientArea;
	}

	int Game::getResult()
	{
		if (currentAction == TYPES::ACTION_LIST::NATION_SELECTION)
		{
			selectedNation = std::make_unique<Nation>(nationSelectionMenu->selectedItem());
			currentAction = TYPES::ACTION_LIST::START_GAME;
		}

		return 0;
	}

	const int Game::getWindowHeight()
	{
		return WINDOW_HEIGHT;
	}

	const int Game::getWindowWidth()
	{
		return WINDOW_WIDTH;
	}

	void Game::handleGameEvent(SDL_Event e)
	{
		if (e.type == SDL_KEYDOWN)
		{
			if (e.key.keysym.sym == SDLK_DOWN)
			{
				nationSelectionMenu->nextMenuItem();
			}
			else if (e.key.keysym.sym == SDLK_UP)
			{
				nationSelectionMenu->previousMenuItem();
			}
			else if (e.key.keysym.sym == SDLK_RETURN)
			{
				nationSelectionMenu->selectCurrentItem();
			}
		}
		else if (e.type == SDL_MOUSEBUTTONDOWN)
		{
			if (e.button.button == SDL_BUTTON_LEFT)
			{
				nationSelectionMenu->handleClick(e.button.x, e.button.y);
			}
		}
	}

	void Game::handleMenuEvent(SDL_Event e)
	{
		if (e.type == SDL_KEYDOWN)
		{
			if (e.key.keysym.sym == SDLK_DOWN)
			{
				aMenu->nextMenuItem();
			}
			else if (e.key.keysym.sym == SDLK_UP)
			{
				aMenu->previousMenuItem();
			}
			else if (e.key.keysym.sym == SDLK_RETURN)
			{
				aMenu->selectCurrentItem();
			}
		}
		else if (e.type == SDL_MOUSEBUTTONDOWN)
		{
			if (e.button.button == SDL_BUTTON_LEFT)
			{
				aMenu->handleClick(e.button.x, e.button.y);
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
		window = SDL_CreateWindow("Global Domination", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, 0);
		if (!window) {
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Window creation fail : %s\n", SDL_GetError());
			return;
		}

		surface = SDL_GetWindowSurface(window);
		renderer = SDL_CreateSoftwareRenderer(surface);
		if (!renderer) {
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Render creation for surface fail : %s\n", SDL_GetError());
			return;
		}

		/* Clear the rendering surface with the specified color */
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xFF);
		SDL_RenderClear(renderer);

		TTF_Init();

		initializeMainMenu();
		initializeNationSelectionMenu();
	}

	void Game::initializeMainMenu()
	{
		SDL_Rect clientArea = getClientArea();
		aMenu = std::make_unique<SDLMenu<int>>(window, clientArea);
		aMenu->addMenuItem(MenuItem<int>("PLAY!", std::make_shared<StartGameAction>(this), 0));
		aMenu->addMenuItem(MenuItem<int>("QUIT!", std::make_shared<QuitGameAction>(this), 1));
	}

	void Game::initializeNationSelectionMenu()
	{
		SDL_Rect clientArea = getClientArea();
		nationSelectionMenu = std::make_unique<SDLMenu<Nation>>(window, clientArea);

		float textLocationY = 0.05f;
		for (std::vector<Nation>::const_iterator nation = nations.cbegin(); nation != nations.end(); nation++)
		{
			SDL_Rect textLocation = { (int)(clientArea.w * 0.45), (int)(clientArea.h * textLocationY), 0, 0 };
			std::shared_ptr<NationSelectionAction> nationSelectionAction = std::make_shared<NationSelectionAction>(this);
			std::string nationName = nation->reportString();
			nationSelectionMenu->addMenuItem(MenuItem<Nation>(nationName, nationSelectionAction, *nation));
			textLocationY += 0.1f;
		}
	}

	void Game::render()
	{
		switch (currentAction)
		{
		case TYPES::ACTION_LIST::MENU:
		{
			aMenu->renderMenu(renderer);
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
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xFF);
		SDL_RenderClear(renderer);

		SDL_Rect darea = getClientArea();
		SDL_Rect textLocationTitle = { (int)(darea.w * 0.25), (int)(darea.h * 0.05), 0, 0 };
		SDL_TextRenderer::renderText(window, "GLOBAL DOMINATION!", textLocationTitle, { 0, 255, 0 });

		SDL_Rect textLocationSelectNation = { (int)(darea.w * 0.15), (int)(darea.h * 0.25), 0, 0 };
		SDL_TextRenderer::renderText(window, "Select a nation:", textLocationSelectNation, { 0, 255, 0 });

		nationSelectionMenu->renderMenu(renderer);

		SDL_UpdateWindowSurface(window);
	}

	void Game::runGameLoop()
	{
		while (currentAction != TYPES::ACTION_LIST::QUIT)
		{
			update();
			render();
		}
	}

	void Game::setAction(TYPES::ACTION_LIST action)
	{
		currentAction = action;
	}

	void Game::update()
	{
		SDL_Event e;

		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				currentAction = TYPES::ACTION_LIST::QUIT;
				return;
			}

			if ((e.type == SDL_KEYDOWN) && (e.key.keysym.sym == SDLK_ESCAPE)) {
				currentAction = TYPES::ACTION_LIST::QUIT;
				return;
			}

			switch (currentAction)
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