#pragma once
#include "SDLControl.h"

#include "Nation.h"

namespace global_domination
{
	class Game;
	class TradeView : public SDLControl
	{
	public:
		TradeView::TradeView(Game* the_game, SDL_Window * parent, SDL_Rect client_area);
		virtual ~TradeView();
		TradeDeal* getSelectedTradeDeal();
		TradeResource* getSelectedTradeResource();
		std::shared_ptr<Action> getTradeDealSelectionAction();
		void initialize();
		void respondToAction(TYPES::ACTION_LIST action);
		void updateExistingTradeDeals();
		void updateProspectiveTradeDeals();
		void updateForSelectedResource();
		void updateForSelectedTradeDeal();
	private:
		Nation* nation_;
		Game* the_game_;
	};
}
