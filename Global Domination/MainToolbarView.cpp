#include "MainToolbarView.h"

#include "Action.h"
#include "Game.h"
#include "SDLButton.h"

namespace global_domination
{
	MainToolbarView::MainToolbarView(Game* the_game, SDL_Window * parent, SDL_Rect client_area) : View(the_game, parent, client_area)
	{
	}

	void MainToolbarView::initialize()
	{
		std::shared_ptr<SDLButton> next_button = std::make_shared<SDLButton>(parent_, "NEXT", std::make_shared<Action>(the_game_, TYPES::ACTION_LIST::NEXT_TURN), client_area_.w * 0.8, client_area_.h * 0.05, 200, 300);
		addControl(next_button);
	}

	void MainToolbarView::respondToAction(TYPES::ACTION_LIST action)
	{

	}
}
