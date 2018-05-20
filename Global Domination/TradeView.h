#pragma once
#include "SDLCompositePane.h"

#include "Nation.h"

namespace global_domination
{
	class GameModel;
	class TradeView : public SDLCompositePane
	{
	public:
		TradeView::TradeView(GameModel& the_model, SDL_Window * parent, SDL_Rect client_area);
		virtual ~TradeView();
		void acceptTradeOffer();
		void cancelTradeDeal();
		TradeDeal* getSelectedTradeDeal();
		TradeResource* getSelectedTradeResource();
		std::shared_ptr<Action> getTradeDealSelectionAction();
		void initialize();
		void rejectTradeOffer();
		void respondToAction(Sint32 action);
		void showTradeDeals();
		void showTradeOffers();
		void updateExistingTradeDeals();
		void updateTradeOffers();
		void updateForSelectedResource();
		void updateForSelectedTradeDeal();
	private:
		Nation* nation_;
		GameModel& game_model_;
	};
}
