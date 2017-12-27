#include "TradeDealsView.h"

#include "SDLListBox.h"
#include "TradeDeal.h"

namespace global_domination
{
	TradeDealsView::TradeDealsView(Game * the_game, SDL_Window * parent, SDL_Rect client_area) : SDLCompositePane(parent, client_area)
	{
		initialize();
	}

	void TradeDealsView::initialize()
	{
		SDL_Rect trade_deals_list_client_area{ client_area_.x, client_area_.y, client_area_.w * 0.5, client_area_.h };
		std::shared_ptr<SDLListBox<TradeDeal>> trade_deal_list = std::make_shared<SDLListBox<TradeDeal>>(parent_, trade_deals_list_client_area, client_area_.h * 0.1);
		trade_deal_list->setId(TRADE_DEAL_LIST);
		addChildControl(trade_deal_list);
	}

	void TradeDealsView::respondToAction(TYPES::ACTION_LIST action)
	{
	}
}