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
		addLabel("GDP: " + std::to_string(nation_.getGDP()), client_area_.w * 0.25, client_area_.h * 0.4, FINANCES_BALANCE_LABEL, 18);
	}

	void FinancesView::respondToAction(TYPES::ACTION_LIST action)
	{
	}
}
