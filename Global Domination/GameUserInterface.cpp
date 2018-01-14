#include "GameUserInterface.h"
#include "SDL_ttf.h"

#include "FinancesView.h"
#include "InboxView.h"
#include "MainMenuView.h"
#include "NationSelectionView.h"
#include "RelationsView.h"
#include "TradeView.h"
#include "WorldView.h"

namespace global_domination
{

	GameUserInterface::GameUserInterface()
	{
		is_quiting_ = false;
	}

	SDL_Rect GameUserInterface::getClientArea() const
	{
		SDL_Rect client_area;
		SDL_RenderGetViewport(renderer_, &client_area);
		return client_area;
	}

	void GameUserInterface::initialize(std::shared_ptr<GameModel> the_model)
	{
		game_model_ = the_model;

		SDL_Surface *surface;

		/* Enable standard application logging */
		SDL_LogSetPriority(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO);

		/* Initialize SDL */
		if (SDL_Init(SDL_INIT_VIDEO) != 0) {
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_Init fail : %s\n", SDL_GetError());
			return;
		}

		/* Create window and renderer for given surface */
		window_ = SDL_CreateWindow("Global Domination", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1024, 800, 0  /*SDL_WINDOW_FULLSCREEN */);
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

		SDL_Rect toolbar_client_area = getClientArea();
		toolbar_client_area.h = (int)(toolbar_client_area.h * 0.1);
		toolbar_ = std::make_unique<MainToolbarView>(game_model_, window_, toolbar_client_area);
		toolbar_->initialize();
		toolbar_->setVisibility(false);

		TTF_Init();
	}

	bool GameUserInterface::isQuiting()
	{
		return is_quiting_;
	}

	void GameUserInterface::render()
	{
		SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 0xFF);
		SDL_RenderClear(renderer_);

		active_control_->render(renderer_);
		toolbar_->render(renderer_);

		SDL_UpdateWindowSurface(window_);
	}

	void GameUserInterface::respondToAction(Sint32 action)
	{
		game_model_->respondToAction(action);

		if(active_control_)
		{
			toolbar_->respondToAction(action);
			active_control_->respondToAction(action);
		}

		switch (action)
		{
			case TYPES::ACTION_LIST::CHANGEVIEW_MENU:
			{
				switchActiveControl(std::make_unique<MainMenuView>(window_, getClientArea()));
			}
			break;
			case TYPES::ACTION_LIST::CHANGEVIEW_NATIONSELECTION:
			{
				switchActiveControl(std::make_unique<NationSelectionView>(game_model_, window_, getClientArea()));
			}
			break;
			case TYPES::ACTION_LIST::CHANGEVIEW_INBOX:
			{
				toolbar_->setVisibility(true);
				switchActiveControl(std::make_unique<InboxView>(game_model_, window_, getClientArea()));
			}
			break;
			case TYPES::ACTION_LIST::CHANGEVIEW_FINANCES:
			{
				switchActiveControl(std::make_unique<FinancesView>(game_model_, window_, getClientArea()));
			}
			break;
			case TYPES::ACTION_LIST::CHANGEVIEW_RELATIONS:
			{
				switchActiveControl(std::make_unique<RelationsView>(game_model_, window_, getClientArea()));
			}
			break;
			case TYPES::ACTION_LIST::CHANGEVIEW_TRADE:
			{
				switchActiveControl(std::make_unique<TradeView>(game_model_, window_, getClientArea()));
			}
			break;
			case TYPES::ACTION_LIST::CHANGEVIEW_WORLD:
			{
				switchActiveControl(std::make_unique<WorldView>(game_model_, window_, getClientArea()));
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
				if (!toolbar_->handleClick(x, y))
				{
					active_control_->handleClick(x, y);
				}
				
			}
			break;
		}
	}

	void GameUserInterface::switchActiveControl(std::shared_ptr<SDLCompositePane> top_control)
	{
		top_control->initialize();
		active_control_ = top_control;
	}

	void GameUserInterface::update()
	{
		SDL_Event e;

		while (SDL_PollEvent(&e)) {
			
			if (e.type == SDL_QUIT) 
			{
				is_quiting_ = true;
				return;
			}

			if (e.user.code == TYPES::ACTION_LIST::QUIT) {
				is_quiting_ = true;
				return;
			}
	
			if (e.type == SDL_MOUSEBUTTONDOWN)
			{
				if (e.button.button == SDL_BUTTON_LEFT)
				{
					respondToMouseClick(TYPES::ACTION_LIST::MOUSECLICK_LEFT, e.button.x, e.button.y);
				}
			}

			else if((e.type >= SDL_USEREVENT) && (e.type <= SDL_LASTEVENT))
			{
				respondToAction(e.user.code);
			}
		}
	}


}


