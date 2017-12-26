#include "FinancesView.h"

#include "SDLStaticText.h"

namespace global_domination
{
	FinancesView::FinancesView(Game* the_game, SDL_Window * parent, SDL_Rect client_area) : SDLCompositePane(parent, client_area)
	{
		nation_ = the_game->getGameModel()->getSelectedNation();
	}

	FinancesView::~FinancesView()
	{
	}

	void FinancesView::initialize()
	{
		std::shared_ptr<SDLStaticText> title_label = std::make_shared<SDLStaticText>(parent_, "GDP: " + std::to_string(nation_->getGDP()), client_area_.w * 0.25, client_area_.h * 0.4);
		title_label->setId(FINANCES_BALANCE_LABEL);
		title_label->setFontSize(18);

		addChildControl(title_label);
	}

	void FinancesView::respondToAction(TYPES::ACTION_LIST action)
	{
		switch (action)
		{
			case TYPES::ACTION_LIST::NEXT_TURN:
			{
				std::shared_ptr<SDLStaticText> control = std::dynamic_pointer_cast<SDLStaticText>(getChildControl(FINANCES_BALANCE_LABEL));
				control->setText("GDP: " + std::to_string(nation_->getGDP()));
			}
			break;
		}
	}
}
