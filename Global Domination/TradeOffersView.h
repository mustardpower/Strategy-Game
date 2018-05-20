#pragma once

#include "Nation.h"
#include "SDLCompositePane.h"
#include "TradeDeal.h"

namespace global_domination
{
	class GameModel;
	class TradeOffersView : public SDLCompositePane
	{
	public:
		TradeOffersView(GameModel& the_model, SDL_Window * parent, SDL_Rect client_area);
		TradeDeal* getSelectedTradeOffer();
		void initialize();
		void respondToAction(Sint32 action);
		void updateGui();
		
	private:
		GameModel& game_model_;
		Nation* nation_;
	};
}