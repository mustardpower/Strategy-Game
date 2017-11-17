#include "InboxView.h"

#include "ViewModel.h"
#include "SDLStaticText.h"

namespace global_domination {

	InboxView::InboxView(Game* the_game, SDL_Window * parent, SDL_Rect client_area) : View(std::make_unique<ViewModel>(the_game), parent, client_area)
	{
	}

	void InboxView::initialize()
	{
		std::shared_ptr<SDLStaticText> title_label = std::make_shared<SDLStaticText>(parent_, "INBOX", client_area_.w * 0.25, client_area_.h * 0.05);
		addControl(title_label);
	}
	void InboxView::onKeyDown()
	{
	}
	void InboxView::onKeyUp()
	{
	}
	void InboxView::onKeyPress(int keyCode)
	{
	}
}
