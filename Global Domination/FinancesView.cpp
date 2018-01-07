#include "FinancesView.h"

#include "SDLStaticText.h"

namespace global_domination
{
	FinancesView::FinancesView(std::shared_ptr<GameModel> the_model, SDL_Window * parent, SDL_Rect client_area) : SDLCompositePane(parent, client_area)
	{
		nation_ = the_model->getSelectedNation();
	}

	FinancesView::~FinancesView()
	{
	}

	void FinancesView::initialize()
	{
		std::shared_ptr<SDLStaticText> title_label = std::make_shared<SDLStaticText>(parent_, "GDP: " + std::to_string(nation_->getGDP()), (int)(client_area_.w * 0.25), (int)(client_area_.h * 0.4));
		title_label->setId(FINANCES_BALANCE_LABEL);
		title_label->setFontSize(18);

		addChildControl(title_label);
	}

	void FinancesView::respondToAction(Sint32 action)
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
