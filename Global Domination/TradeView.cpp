#include "TradeView.h"

#include <memory>

#include "Action.h"
#include "ControlResources.h"
#include "Game.h"
#include "SDLButton.h"
#include "SDLListBox.h"
#include "SDLStackGrid.h"
#include "TradeDeal.h"

namespace global_domination
{
	TradeView::TradeView(Game * the_game, SDL_Window * parent, SDL_Rect client_area) : View(the_game, parent, client_area)
	{
		nation_ = the_game->getGameModel()->getSelectedNation();
	}
	TradeView::~TradeView()
	{
	}
	void TradeView::initialize()
	{
		addLabel("Trade offers:", client_area_.w * 0.08, client_area_.h * 0.15, TRADEVIEW_TRADEDEALS_LABEL);
		SDL_Rect trade_deal_list_area{ client_area_.w * 0.08, client_area_.h * 0.2, client_area_.w * 0.25, client_area_.h * 0.5 };
		std::shared_ptr<SDLListBox<TradeDeal>> trade_deal_list = std::make_shared<SDLListBox<TradeDeal>>(parent_, trade_deal_list_area, client_area_.h * 0.1);
		trade_deal_list->setId(TRADE_DEAL_LIST);

		addLabel("Existing deals:", client_area_.w * 0.35, client_area_.h * 0.15, TRADEVIEW_TRADEDEALS_LABEL);
		SDL_Rect existing_trade_deal_list_area{ client_area_.w * 0.35, client_area_.h * 0.2, client_area_.w * 0.25, client_area_.h * 0.5 };
		std::shared_ptr<SDLListBox<TradeDeal>> existing_trade_deal_list = std::make_shared<SDLListBox<TradeDeal>>(parent_, existing_trade_deal_list_area, client_area_.h * 0.1);
		existing_trade_deal_list->setId(TRADE_DEAL_LIST_EXISTING);

		addLabel("Resources:", client_area_.w * 0.08, client_area_.h * 0.7, TRADEVIEW_TRADEDEALS_LABEL);
		SDL_Rect resource_list_area{ client_area_.w * 0.06, client_area_.h * 0.75, client_area_.w * 0.88, client_area_.h * 0.2 };
		std::shared_ptr<SDLStackGrid<TradeResource, 10, 2>> resource_list = std::make_shared<SDLStackGrid<TradeResource, 10, 2>>(parent_, resource_list_area);
		resource_list->setId(TRADE_RESOURCE_LIST);

		std::map<TradeResource, int> trade_resources = nation_.getTradeResources();
		std::shared_ptr<Action> trade_deal_selection_action = std::make_shared<Action>(the_game_, TYPES::ACTION_LIST::SELECTING_TRADE_DEAL);
		for (std::map<TradeResource, int>::const_iterator resource = trade_resources.cbegin(); resource != trade_resources.end(); resource++)
		{
			TradeResource trade_resource = (*resource).first;
			resource_list->addItemAtNextFreeSlot(StackGridItem<TradeResource>(trade_deal_selection_action, trade_resource));
		}

		std::vector<TradeDeal> trade_deals = nation_.getTradeDeals();
		for (std::vector<TradeDeal>::const_iterator deal = trade_deals.cbegin(); deal != trade_deals.end(); deal++)
		{
			trade_deal_list->addItem(ListItem<TradeDeal>(deal->getPayee(), trade_deal_selection_action, *deal));
		}

		addControl(resource_list);
		addControl(existing_trade_deal_list);
		addControl(trade_deal_list);
	}
	void TradeView::respondToAction(TYPES::ACTION_LIST action)
	{
	}
}
