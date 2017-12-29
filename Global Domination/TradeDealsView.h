#pragma once

#include "SDLCompositePane.h"
#include "TradeDeal.h"

namespace global_domination
{
	class GameModel;
	class TradeDealsView : public SDLCompositePane
	{
	public:
		TradeDealsView(std::shared_ptr<GameModel> the_model, SDL_Window * parent, SDL_Rect client_area);
		TradeDeal* getSelectedTradeDeal();
		void initialize();
		void respondToAction(Sint32 action);

	private:
		std::shared_ptr<GameModel> game_model_;
	};
}