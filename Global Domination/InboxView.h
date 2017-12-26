#pragma once
#include "SDLControl.h"
#include "IReciever.h"

namespace global_domination
{
	class Game;

	class InboxView : public SDLControl
	{
	public:
		InboxView::InboxView(Game* the_game, SDL_Window * parent, SDL_Rect client_area);
		void initialize();
		void respondToAction(TYPES::ACTION_LIST action);
		void updateMessageList();
		void updateSelectedMessageText();
	private:
		Game* the_game_;
	};
}
