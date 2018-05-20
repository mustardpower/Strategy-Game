#pragma once

#include "SDLCompositePane.h"
#include "TradeDeal.h"

namespace global_domination
{
	class GameModel;
	class TradeDealsView : public SDLCompositePane
	{
	public:
		TradeDealsView(GameModel& the_model, SDL_Window * parent, SDL_Rect client_area);
		TradeDeal* getSelectedTradeDeal();
		void initialize();
		void respondToAction(Sint32 action);
		void updateGui();

	private:
		GameModel& game_model_;
	};
}