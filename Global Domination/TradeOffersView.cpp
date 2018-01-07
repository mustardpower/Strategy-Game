#include "TradeOffersView.h"

#include "Game.h"
#include "SDLButton.h"
#include "SDLListBox.h"

namespace global_domination
{
	TradeOffersView::TradeOffersView(std::shared_ptr<GameModel> the_model, SDL_Window * parent, SDL_Rect client_area) : SDLCompositePane(parent, client_area)
	{
		game_model_ = the_model;
		nation_ = the_model->getSelectedNation();

		initialize();
	}

	TradeDeal* TradeOffersView::getSelectedTradeOffer()
	{
		std::shared_ptr<SDLListBox<TradeDeal>> trade_deal_list = std::dynamic_pointer_cast<SDLListBox<TradeDeal>>(getChildControl(TRADE_OFFERS_LIST));
		return trade_deal_list->selectedItem();
	}

	void TradeOffersView::initialize()
	{
		SDL_Rect trade_offers_list_client_area{ client_area_.x, client_area_.y, (int)(client_area_.w * 0.5), client_area_.h };
		std::shared_ptr<SDLListBox<TradeDeal>> trade_offers_list = std::make_shared<SDLListBox<TradeDeal>>(parent_, trade_offers_list_client_area);
		trade_offers_list->setId(TRADE_OFFERS_LIST);
		addChildControl(trade_offers_list);

		SDL_Rect accept_button_client_area{ client_area_.x + (int)(client_area_.w * 0.6), client_area_.y + (int)(client_area_.h * 0.2), 100, (int)(client_area_.h * 0.05) };
		std::shared_ptr<SDLButton> accept_offer_button = std::make_shared<SDLButton>(parent_, "Accept offer", std::make_shared<Action>(TYPES::ACTION_LIST::TRADEVIEW_ACCEPT_OFFER), accept_button_client_area);
		accept_offer_button->setFontSize(12);
		accept_offer_button->setId(TRADEVIEW_ACCEPTOFFER_BUTTON);
		addChildControl(accept_offer_button);

		SDL_Rect decline_button_client_area{ client_area_.x + (int)(client_area_.w * 0.8), client_area_.y + (int)(client_area_.h * 0.2), 100, (int)(client_area_.h * 0.05) };
		std::shared_ptr<SDLButton> decline_offer_button = std::make_shared<SDLButton>(parent_, "Decline offer", std::make_shared<Action>(TYPES::ACTION_LIST::TRADEVIEW_DECLINE_OFFER), decline_button_client_area);
		decline_offer_button->setFontSize(12);
		decline_offer_button->setId(TRADEVIEW_DECLINEOFFER_BUTTON);
		addChildControl(decline_offer_button);
	}

	void TradeOffersView::respondToAction(Sint32 action)
	{
		switch (action)
		{
			case TYPES::ACTION_LIST::TRADEVIEW_ACCEPT_OFFER:
			{
				TradeDeal* trade_offer = getSelectedTradeOffer();
				if (trade_offer)
				{
					nation_->acceptTradeOffer(*trade_offer);
				}
			}
			break;
			case TYPES::ACTION_LIST::TRADEVIEW_DECLINE_OFFER:
			{
				TradeDeal* trade_offer = getSelectedTradeOffer();
				if (trade_offer)
				{
					nation_->declineTradeOffer(*trade_offer);
				}
			}
			break;
		}
	}

	void TradeOffersView::updateGui()
	{
		std::shared_ptr<SDLListBox<TradeDeal>> trade_offers_list = std::dynamic_pointer_cast<SDLListBox<TradeDeal>>(getChildControl(TRADE_OFFERS_LIST));
		std::shared_ptr<SDLButton> accept_offer_button = std::dynamic_pointer_cast<SDLButton>(getChildControl(TRADEVIEW_ACCEPTOFFER_BUTTON));
		accept_offer_button->setVisibility(!trade_offers_list->isEmpty());
		std::shared_ptr<SDLButton> decline_offer_button = std::dynamic_pointer_cast<SDLButton>(getChildControl(TRADEVIEW_DECLINEOFFER_BUTTON));
		decline_offer_button->setVisibility(!trade_offers_list->isEmpty());
	}
}

