#include "TradeView.h"

#include <memory>

#include "Action.h"
#include "ControlResources.h"
#include "Game.h"
#include "SDLButton.h"
#include "SDLListBox.h"
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
		addLabel("Trade deals:", client_area_.w * 0.15, client_area_.h * 0.25, NATION_SELECTION_PROMPT_LABEL);

		SDL_Rect menu_client_area{ client_area_.w * 0.2, client_area_.h * 0.4, client_area_.w * 0.3, client_area_.h * 0.5 };
		std::shared_ptr<SDLListBox<TradeDeal>> trade_deal_list = std::make_shared<SDLListBox<TradeDeal>>(parent_, menu_client_area, client_area_.h * 0.1);
		trade_deal_list->setId(TRADE_DEAL_LIST);

		std::shared_ptr<Action> trade_deal_selection_action = std::make_shared<Action>(the_game_, TYPES::ACTION_LIST::SELECTING_TRADE_DEAL);

		std::vector<TradeDeal> trade_deals = nation_.getTradeDeals();
		for (std::vector<TradeDeal>::const_iterator deal = trade_deals.cbegin(); deal != trade_deals.end(); deal++)
		{
			trade_deal_list->addItem(ListItem<TradeDeal>(deal->getPayee(), trade_deal_selection_action, *deal));
		}

		addControl(trade_deal_list);
	}
	void TradeView::respondToAction(TYPES::ACTION_LIST action)
	{
	}
}
