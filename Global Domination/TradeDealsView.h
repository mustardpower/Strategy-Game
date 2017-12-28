#pragma once

#include "SDLCompositePane.h"
#include "TradeDeal.h"

namespace global_domination
{
	class Game;
	class TradeDealsView : public SDLCompositePane
	{
	public:
		TradeDealsView(Game* the_game, SDL_Window * parent, SDL_Rect client_area);
		TradeDeal* getSelectedTradeDeal();
		void initialize();
		void respondToAction(TYPES::ACTION_LIST action);

	private:
		Game* the_game_;
	};
}