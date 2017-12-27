#pragma once

#include "SDLCompositePane.h"

namespace global_domination
{
	class Game;
	class TradeOffersView : public SDLCompositePane
	{
	public:
		TradeOffersView(Game* the_game, SDL_Window * parent, SDL_Rect client_area);
		void initialize();
		void respondToAction(TYPES::ACTION_LIST action);
		
	private:
	};
}