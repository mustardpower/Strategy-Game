#pragma once
#include "SDLCompositePane.h"

namespace global_domination
{
	class GameModel;

	class InboxView : public SDLCompositePane
	{
	public:
		InboxView::InboxView(GameModel& the_model, SDL_Window * parent, SDL_Rect client_area);
		void initialize();
		void respondToAction(Sint32 action);
		void updateMessageList();
		void updateSelectedMessageText();
	private:
		GameModel& game_model_;
	};
}
