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
		current_action_ = TYPES::ACTION_LIST::UNINITIALIZED;
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
		switch (current_action_)
		{
			case TYPES::ACTION_LIST::MENU:
			{
				switchActiveView(std::make_unique<MainMenuView>(viewReciever_, window_, getClientArea()));
			}
			break;
			case TYPES::ACTION_LIST::NATION_SELECTION:
			{
				switchActiveView(std::make_unique<NationSelectionView>(viewReciever_, window_, getClientArea()));
			}
			break;
			case TYPES::ACTION_LIST::INBOX:
			{
				switchActiveView(std::make_unique<InboxView>(viewReciever_, window_, getClientArea()));
			}
			break;
		}

		return 0;
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

		/*Calling shared_from_this() requires that there is at least one shared_ptr instance already pointing to your object.
		If you use it on an automatic object without a shared_ptr instance with a custom deleter then you will get bad stuff happening.*/
		viewReciever_ = shared_from_this();

		/* Fake an action trigger to initialize the first view */
		setAction(TYPES::ACTION_LIST::MENU);
		getResult();
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
		if (current_action_ != action)
		{
			current_action_ = action;
		}
	}

	void Game::switchActiveView(std::shared_ptr<View> view)
	{
		view->initialize();

		if (active_view_)
		{
			// need to transfer reciever ptr so reference count is correct
			// if not correct then the ptr will be destroyed and the reciever will
			// be destroyed too!
			view->setReciever(active_view_->getReciever());
		}
		
		active_view_ = view;
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
					active_view_->onKeyDown();
				}
				else if (e.key.keysym.sym == SDLK_UP)
				{
					active_view_->onKeyUp();
				}
				else if (e.key.keysym.sym == SDLK_RETURN)
				{
					active_view_->onKeyPress(SDLK_RETURN);
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
	}
}