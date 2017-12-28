#pragma once

#include "Nation.h"
#include "SDLCompositePane.h"
#include "TradeDeal.h"

namespace global_domination
{
	class Game;
	class TradeOffersView : public SDLCompositePane
	{
	public:
		TradeOffersView(Game* the_game, SDL_Window * parent, SDL_Rect client_area);
		TradeDeal* getSelectedTradeOffer();
		void initialize();
		void respondToAction(TYPES::ACTION_LIST action);
		void updateGui();
		
	private:
		Game* the_game_;
		Nation* nation_;
	};
}