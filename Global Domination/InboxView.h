#pragma once
#include "View.h"

namespace global_domination
{
	class Game;

	class InboxView : public View
	{
	public:
		InboxView::InboxView(Game* the_game, SDL_Window * parent, SDL_Rect client_area);
		void initialize();
		void respondToAction(TYPES::ACTION_LIST action);
		void updateMessageList();
	private:
	};
}
