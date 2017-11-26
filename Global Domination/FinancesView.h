#pragma once
#include "View.h"

#include "Nation.h"

namespace global_domination
{
	class FinancesView : public View
	{
	public:
		FinancesView::FinancesView(Game* the_game, SDL_Window * parent, SDL_Rect client_area);
		virtual ~FinancesView();
		void initialize();
		void respondToAction(TYPES::ACTION_LIST action);
	private:
		Nation nation_;
	};
}