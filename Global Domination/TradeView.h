#pragma once
#include "View.h"

#include "Nation.h"

namespace global_domination
{
	class TradeView : public View
	{
	public:
		TradeView::TradeView(Game* the_game, SDL_Window * parent, SDL_Rect client_area);
		virtual ~TradeView();
		TradeDeal* getSelectedTradeDeal();
		TradeResource* getSelectedTradeResource();
		std::shared_ptr<Action> getTradeDealSelectionAction();
		void initialize();
		void respondToAction(TYPES::ACTION_LIST action);
		void updateForSelectedResource();
		void updateForSelectedTradeDeal();
	private:
		Nation nation_;
	};
}
