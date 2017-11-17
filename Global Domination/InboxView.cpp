#include "InboxView.h"

#include "Game.h"
#include "SDLStaticText.h"

namespace global_domination {

	InboxView::InboxView(Game* the_game, SDL_Window * parent, SDL_Rect client_area) : View(the_game, parent, client_area)
	{
	}

	void InboxView::initialize()
	{
		std::shared_ptr<SDLStaticText> title_label = std::make_shared<SDLStaticText>(parent_, "INBOX", client_area_.w * 0.25, client_area_.h * 0.05);
		addControl(title_label);
		
		std::string nation_name = the_game_->getGameModel()->getSelectedNationName();
		std::shared_ptr<SDLStaticText> name_label = std::make_shared<SDLStaticText>(parent_, nation_name, client_area_.w * 0.25, client_area_.h * 0.25);
		addControl(name_label);
	}
	
	void InboxView::respondToAction(TYPES::ACTION_LIST action)
	{
	}
}
