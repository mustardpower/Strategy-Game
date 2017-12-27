#include "TradeDealsView.h"

#include "SDLListBox.h"
#include "TradeDeal.h"

namespace global_domination
{
	TradeDealsView::TradeDealsView(Game * the_game, SDL_Window * parent, SDL_Rect client_area) : SDLCompositePane(parent, client_area)
	{
	}

	void TradeDealsView::initialize()
	{
		std::shared_ptr<SDLListBox<TradeDeal>> trade_deal_list = std::make_shared<SDLListBox<TradeDeal>>(parent_, client_area_, client_area_.h * 0.1);
		trade_deal_list->setId(TRADE_DEAL_LIST);
		addChildControl(trade_deal_list);
	}

	void TradeDealsView::respondToAction(TYPES::ACTION_LIST action)
	{
	}
}