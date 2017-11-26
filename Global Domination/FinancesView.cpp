#include "FinancesView.h"

#include "Game.h"
#include "SDLStaticText.h"

namespace global_domination
{
	FinancesView::FinancesView(Game* the_game, SDL_Window * parent, SDL_Rect client_area) : View(the_game, parent, client_area)
	{
		nation_ = the_game->getGameModel()->getSelectedNation();
	}

	FinancesView::~FinancesView()
	{
	}

	void FinancesView::initialize()
	{
		std::shared_ptr<SDLStaticText> bank_balance_label = std::make_shared<SDLStaticText>(parent_, "GDP: " + std::to_string(nation_.getGDP()), client_area_.w * 0.25, client_area_.h * 0.4);
		bank_balance_label->setFontSize(18);
		addControl(bank_balance_label);
	}

	void FinancesView::respondToAction(TYPES::ACTION_LIST action)
	{
	}
}
