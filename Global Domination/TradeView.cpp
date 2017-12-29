#include "TradeView.h"

#include <memory>

#include "Action.h"
#include "ControlResources.h"
#include "GameModel.h"
#include "SDLButton.h"
#include "SDLButtonGroup.h"
#include "SDLListBox.h"
#include "SDLStackGrid.h"
#include "TradeDeal.h"
#include "TradeDealsView.h"
#include "TradeOffersView.h"

namespace global_domination
{
	TradeView::TradeView(std::shared_ptr<GameModel> the_model, SDL_Window * parent, SDL_Rect client_area) : SDLCompositePane(parent, client_area)
	{
		game_model_ = the_model;
		nation_ = game_model_->getSelectedNation();
	}

	TradeView::~TradeView()
	{
	}

	void TradeView::acceptTradeOffer()
	{
		std::shared_ptr<TradeOffersView> trade_offer_pane = std::dynamic_pointer_cast<TradeOffersView>(getChildControl(TRADE_OFFERS_PANE));
		TradeDeal* trade_offer = trade_offer_pane->getSelectedTradeOffer();
		if (trade_offer)
		{
			nation_->acceptTradeOffer(*trade_offer);
			updateForSelectedResource();
		}
	}

	void TradeView::cancelTradeDeal()
	{
		std::shared_ptr<TradeDealsView> trade_deal_pane = std::dynamic_pointer_cast<TradeDealsView>(getChildControl(TRADE_DEALS_PANE));
		TradeDeal* trade_deal = trade_deal_pane->getSelectedTradeDeal();
		if (trade_deal)
		{
			nation_->cancelTradeDeal(*trade_deal);
			updateForSelectedResource();
		}
	}

	TradeDeal* TradeView::getSelectedTradeDeal()
	{
		std::shared_ptr<SDLListBox<TradeDeal>> trade_deal_list = std::dynamic_pointer_cast<SDLListBox<TradeDeal>>(getChildControl(TRADE_DEAL_LIST));
		return trade_deal_list->selectedItem();
	}

	TradeResource * TradeView::getSelectedTradeResource()
	{
		std::shared_ptr<SDLStackGrid<TradeResource, 10, 2>> resource_list = std::dynamic_pointer_cast<SDLStackGrid<TradeResource, 10, 2>>(getChildControl(TRADE_RESOURCE_LIST));
		return resource_list->selectedItem();
	}

	std::shared_ptr<Action> TradeView::getTradeDealSelectionAction()
	{
		return std::make_shared<Action>(TYPES::ACTION_LIST::SELECTING_TRADE_DEAL);
	}

	void TradeView::initialize()
	{
		addLabel("Resource:", client_area_.w * 0.7, client_area_.h * 0.2, TRADEVIEW_DEAL_RESOURCE_LABEL, 15);
		addLabel("Value per annum:", client_area_.w * 0.7, client_area_.h * 0.25, TRADEVIEW_DEAL_VALUEPERANNUM_LABEL, 15);
		addLabel("Total value:", client_area_.w * 0.7, client_area_.h * 0.3, TRADEVIEW_DEAL_TOTALVALUE_LABEL, 15);
		addLabel("Expiry date:", client_area_.w * 0.7, client_area_.h * 0.35, TRADEVIEW_DEAL_EXPIRYDATE_LABEL, 15);

		SDL_Rect offers_button_client_area{ client_area_.w * 0.08, client_area_.h * 0.12, 80, 15 };
		std::shared_ptr<SDLButton> trade_offers_button = std::make_shared<SDLButton>(parent_, "Trade offers", std::make_shared<Action>(TYPES::ACTION_LIST::TRADEVIEW_SHOW_OFFERS), offers_button_client_area);
		trade_offers_button->setFontSize(12);
		addChildControl(trade_offers_button);

		SDL_Rect deals_button_client_area{ client_area_.w * 0.16, client_area_.h * 0.12, 80, 15 };
		std::shared_ptr<SDLButton> trade_deals_button = std::make_shared<SDLButton>(parent_, "Trade deals", std::make_shared<Action>(TYPES::ACTION_LIST::TRADEVIEW_SHOW_DEALS), deals_button_client_area);
		trade_deals_button->setFontSize(12);
		addChildControl(trade_deals_button);

		SDLButtonGroup* buttonGroup = new SDLButtonGroup();
		buttonGroup->addToGroup(trade_offers_button.get());
		buttonGroup->addToGroup(trade_deals_button.get());
		addButtonGroup(buttonGroup);

		SDL_Rect trade_deals_pane_client_area{ client_area_.w * 0.08, client_area_.h * 0.2, client_area_.w * 0.55, client_area_.h * 0.5 };
		std::shared_ptr<TradeDealsView> trade_deals_pane = std::make_shared<TradeDealsView>(game_model_, parent_, trade_deals_pane_client_area);
		trade_deals_pane->setId(TRADE_DEALS_PANE);

		std::shared_ptr<TradeOffersView> trade_offers_pane = std::make_shared<TradeOffersView>(game_model_, parent_, trade_deals_pane_client_area);
		trade_offers_pane->setId(TRADE_OFFERS_PANE);

		addLabel("Resources:", client_area_.w * 0.08, client_area_.h * 0.7, TRADEVIEW_RESOURCES_LABEL);
		SDL_Rect resource_list_area{ client_area_.w * 0.06, client_area_.h * 0.75, client_area_.w * 0.88, client_area_.h * 0.2 };
		std::shared_ptr<SDLStackGrid<TradeResource, 10, 2>> resource_list = std::make_shared<SDLStackGrid<TradeResource, 10, 2>>(parent_, resource_list_area);
		resource_list->setId(TRADE_RESOURCE_LIST);

		std::map<TradeResource, int> trade_resources = nation_->getTradeResources();
		std::shared_ptr<Action> resource_selection_action = std::make_shared<Action>(TYPES::ACTION_LIST::SELECTING_RESOURCE);
		for (std::map<TradeResource, int>::const_iterator resource = trade_resources.cbegin(); resource != trade_resources.end(); resource++)
		{
			TradeResource trade_resource = (*resource).first;
			resource_list->addItemAtNextFreeSlot(StackGridItem<TradeResource>(resource_selection_action, trade_resource));
		}

		addChildControl(resource_list);
		addChildControl(trade_deals_pane);
		addChildControl(trade_offers_pane);

		updateForSelectedResource();
	}

	void TradeView::rejectTradeOffer()
	{
		std::shared_ptr<TradeOffersView> trade_offer_pane = std::dynamic_pointer_cast<TradeOffersView>(getChildControl(TRADE_OFFERS_PANE));
		TradeDeal* trade_offer = trade_offer_pane->getSelectedTradeOffer();
		if (trade_offer)
		{
			nation_->declineTradeOffer(*trade_offer);
			updateForSelectedResource();
		}
	}

	void TradeView::respondToAction(Sint32 action)
	{
		switch (action)
		{
			case TYPES::ACTION_LIST::NEXT_TURN:
			{
				updateForSelectedResource();
			}
			break;
			case TYPES::ACTION_LIST::SELECTING_RESOURCE:
			{
				updateForSelectedResource();
			}
			break;
			case TYPES::ACTION_LIST::SELECTING_TRADE_DEAL:
			{
				updateForSelectedTradeDeal();
			}
			break;
			case TYPES::ACTION_LIST::TRADEVIEW_SHOW_DEALS:
			{
				showTradeDeals();
			}
			break;
			case TYPES::ACTION_LIST::TRADEVIEW_SHOW_OFFERS:
			{
				showTradeOffers();
			}
			break;
			case TYPES::ACTION_LIST::TRADEVIEW_ACCEPT_OFFER:
			{
				acceptTradeOffer();
			}
			break;
			case TYPES::ACTION_LIST::TRADEVIEW_DECLINE_OFFER:
			{
				rejectTradeOffer();
			}
			break;
			case TYPES::ACTION_LIST::TRADEVIEW_CANCEL_DEAL:
			{
				cancelTradeDeal();
			}
		}
	}

	void TradeView::showTradeDeals()
	{
		std::shared_ptr<TradeDealsView> trade_deal_list = std::dynamic_pointer_cast<TradeDealsView>(getChildControl(TRADE_DEALS_PANE));
		trade_deal_list->setVisibility(true);

		std::shared_ptr<TradeOffersView> trade_offers_list = std::dynamic_pointer_cast<TradeOffersView>(getChildControl(TRADE_OFFERS_PANE));
		trade_offers_list->setVisibility(false);
	}

	void TradeView::showTradeOffers()
	{
		std::shared_ptr<TradeDealsView> trade_deal_pane = std::dynamic_pointer_cast<TradeDealsView>(getChildControl(TRADE_DEALS_PANE));
		trade_deal_pane->setVisibility(false);

		std::shared_ptr<TradeOffersView> trade_offers_pane = std::dynamic_pointer_cast<TradeOffersView>(getChildControl(TRADE_OFFERS_PANE));
		trade_offers_pane->setVisibility(true);
		trade_offers_pane->updateGui();
	}

	void TradeView::updateExistingTradeDeals()
	{
		TradeResource* trade_resource = getSelectedTradeResource();
		std::shared_ptr<SDLListBox<TradeDeal>> trade_deal_list = std::dynamic_pointer_cast<SDLListBox<TradeDeal>>(getChildControl(TRADE_DEAL_LIST));
		trade_deal_list->clearItems();
		std::vector<TradeDeal> trade_deals_for_resource = nation_->getTradeDealsForResource(*trade_resource);
		for (std::vector<TradeDeal>::const_iterator deal = trade_deals_for_resource.cbegin(); deal != trade_deals_for_resource.end(); deal++)
		{
			trade_deal_list->addItem(ListItem<TradeDeal>(deal->reportString(), getTradeDealSelectionAction(), *deal));
		}
	}
	void TradeView::updateTradeOffers()
	{
		TradeResource* trade_resource = getSelectedTradeResource();

		std::shared_ptr<SDLListBox<TradeDeal>> trade_offers_list = std::dynamic_pointer_cast<SDLListBox<TradeDeal>>(getChildControl(TRADE_OFFERS_LIST));
		trade_offers_list->clearItems();
		std::vector<TradeDeal> trade_offers_for_resource = nation_->getTradeOffersForResource(*trade_resource);
		for (std::vector<TradeDeal>::const_iterator offer = trade_offers_for_resource.cbegin(); offer != trade_offers_for_resource.end(); offer++)
		{
			trade_offers_list->addItem(ListItem<TradeDeal>(offer->reportString(), getTradeDealSelectionAction(), *offer));
		}

		std::shared_ptr<SDLButton> accept_offer_button = std::dynamic_pointer_cast<SDLButton>(getChildControl(TRADEVIEW_ACCEPTOFFER_BUTTON));
		accept_offer_button->setVisibility(!trade_offers_list->isEmpty());
		std::shared_ptr<SDLButton> decline_offer_button = std::dynamic_pointer_cast<SDLButton>(getChildControl(TRADEVIEW_DECLINEOFFER_BUTTON));
		decline_offer_button->setVisibility(!trade_offers_list->isEmpty());
	}

	void TradeView::updateForSelectedResource()
	{
		if (getSelectedTradeResource())
		{
			updateExistingTradeDeals();
			updateTradeOffers();
			updateForSelectedTradeDeal();
		}
	}
	void TradeView::updateForSelectedTradeDeal()
	{
		TradeDeal* trade_deal = getSelectedTradeDeal();
		if (trade_deal)
		{
			TradeResource selected_resource = trade_deal->getResource();
			setLabelText(TRADEVIEW_DEAL_RESOURCE_LABEL, "Resource: " + selected_resource.reportString());
			setLabelText(TRADEVIEW_DEAL_VALUEPERANNUM_LABEL, "Value per annum: " + trade_deal->reportValuePerAnnum());
			setLabelText(TRADEVIEW_DEAL_TOTALVALUE_LABEL, "Total value: " + trade_deal->reportTotalValue());
			setLabelText(TRADEVIEW_DEAL_EXPIRYDATE_LABEL, "Expiry date: " + trade_deal->reportExpiryDate());
		}
		else
		{
			setLabelText(TRADEVIEW_DEAL_RESOURCE_LABEL, "Resource: N/A");
			setLabelText(TRADEVIEW_DEAL_VALUEPERANNUM_LABEL, "Value per annum: N/A");
			setLabelText(TRADEVIEW_DEAL_TOTALVALUE_LABEL, "Total value: N/A");
			setLabelText(TRADEVIEW_DEAL_EXPIRYDATE_LABEL, "Expiry date: N/A");
		}
	}
}
