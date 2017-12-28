#include "TradeDealsView.h"

#include "Game.h"
#include "SDLButton.h"
#include "SDLListBox.h"
#include "TradeDeal.h"

namespace global_domination
{
	TradeDealsView::TradeDealsView(Game * the_game, SDL_Window * parent, SDL_Rect client_area) : SDLCompositePane(parent, client_area)
	{
		the_game_ = the_game;
		initialize();
	}

	TradeDeal * TradeDealsView::getSelectedTradeDeal()
	{
		std::shared_ptr<SDLListBox<TradeDeal>> trade_deal_list = std::dynamic_pointer_cast<SDLListBox<TradeDeal>>(getChildControl(TRADE_DEAL_LIST));
		return trade_deal_list->selectedItem();
	}

	void TradeDealsView::initialize()
	{
		SDL_Rect trade_deals_list_client_area{ client_area_.x, client_area_.y, client_area_.w * 0.5, client_area_.h };
		std::shared_ptr<SDLListBox<TradeDeal>> trade_deal_list = std::make_shared<SDLListBox<TradeDeal>>(parent_, trade_deals_list_client_area, client_area_.h * 0.1);
		trade_deal_list->setId(TRADE_DEAL_LIST);
		addChildControl(trade_deal_list);

		SDL_Rect cancel_deal_button_client_area{ client_area_.x + client_area_.w * 0.6, client_area_.y + client_area_.h * 0.2, 100, client_area_.h * 0.05 };
		std::shared_ptr<SDLButton> cancel_deal_button = std::make_shared<SDLButton>(parent_, "Cancel deal", std::make_shared<Action>(the_game_, TYPES::ACTION_LIST::TRADEVIEW_CANCEL_DEAL), cancel_deal_button_client_area);
		cancel_deal_button->setFontSize(12);
		cancel_deal_button->setId(TRADEVIEW_CANCELDEAL_BUTTON);
		addChildControl(cancel_deal_button);
	}

	void TradeDealsView::respondToAction(TYPES::ACTION_LIST action)
	{
	}
}