#include "TradeOffersView.h"

#include "SDLListBox.h"
#include "TradeDeal.h"

namespace global_domination
{
	TradeOffersView::TradeOffersView(Game * the_game, SDL_Window * parent, SDL_Rect client_area) : SDLCompositePane(parent, client_area)
	{
	}

	void TradeOffersView::initialize()
	{
		std::shared_ptr<SDLListBox<TradeDeal>> trade_offers_list = std::make_shared<SDLListBox<TradeDeal>>(parent_, client_area_, client_area_.h * 0.1);
		trade_offers_list->setId(TRADE_OFFERS_LIST);
		addChildControl(trade_offers_list);
	}

	void TradeOffersView::respondToAction(TYPES::ACTION_LIST action)
	{
	}
}

