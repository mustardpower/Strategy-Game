#include "GameUserInterface.h"
#include "SDL_ttf.h"

#include "InboxView.h"
#include "MainMenuView.h"
#include "NationSelectionView.h"

namespace global_domination
{

	SDL_Rect GameUserInterface::getClientArea() const
	{
		SDL_Rect client_area;
		SDL_RenderGetViewport(renderer_, &client_area);
		return client_area;
	}

	const int GameUserInterface::getWindowWidth()
	{
		return kWindowWidth;
	}

	const int GameUserInterface::getWindowHeight()
	{
		return kWindowHeight;
	}

	void GameUserInterface::initialize(Game* the_game)
	{
		the_game_ = the_game;

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

		toolbar_ = std::make_unique<MainToolbarView>(the_game_, window_, getClientArea());
		toolbar_->initialize();
		toolbar_->isVisible(false);

		TTF_Init();
	}

	void GameUserInterface::render()
	{
		SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 0xFF);
		SDL_RenderClear(renderer_);

		toolbar_->render(renderer_);
		active_view_->render(renderer_);

		SDL_UpdateWindowSurface(window_);
	}

	void GameUserInterface::respondToAction(TYPES::ACTION_LIST action)
	{
		switch (action)
		{
			case TYPES::ACTION_LIST::CHANGEVIEW_MENU:
			{
				switchActiveView(std::make_unique<MainMenuView>(the_game_, window_, getClientArea()));
			}
			break;
			case TYPES::ACTION_LIST::CHANGEVIEW_NATIONSELECTION:
			{
				switchActiveView(std::make_unique<NationSelectionView>(the_game_, window_, getClientArea()));
			}
			break;
			case TYPES::ACTION_LIST::CHANGEVIEW_INBOX:
			{
				toolbar_->isVisible(true);
				switchActiveView(std::make_unique<InboxView>(the_game_, window_, getClientArea()));
			}
			break;
			case TYPES::ACTION_LIST::KEYPRESS_DOWN:
			{
				active_view_->onKeyDown();
			}
			break;
			case TYPES::ACTION_LIST::KEYPRESS_UP:
			{
				active_view_->onKeyUp();
			}
			break;
			case TYPES::ACTION_LIST::KEYPRESS_RETURN:
			{
				active_view_->onKeyPress(SDLK_RETURN);
			}
			break;
		}
	}

	void GameUserInterface::respondToMouseClick(TYPES::ACTION_LIST action, int x, int y)
	{
		switch (action)
		{
			case TYPES::ACTION_LIST::MOUSECLICK_LEFT:
			{
				toolbar_->handleClick(x, y);
				active_view_->handleClick(x, y);
			}
			break;
		}
	}

	void GameUserInterface::switchActiveView(std::shared_ptr<View> view)
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
}


