#include "RelationsView.h"

#include "Game.h"
#include "SDLProgressBar.h"

namespace global_domination
{
	RelationsView::RelationsView(Game* the_game, SDL_Window * parent, SDL_Rect client_area) : SDLCompositePane(parent, client_area)
	{
	}

	RelationsView::~RelationsView()
	{
	}

	void RelationsView::initialize()
	{
		SDL_Rect progress_bar_client_area{ client_area_.x + client_area_.w * 0.3, client_area_.y + client_area_.h * 0.3, client_area_.w * 0.3, client_area_.h * 0.05 };
		std::shared_ptr<SDLProgressBar> progressBar = std::make_shared<SDLProgressBar>(parent_, progress_bar_client_area);
		addChildControl(progressBar);
	}

	void RelationsView::respondToAction(TYPES::ACTION_LIST action)
	{
		
	}
}
