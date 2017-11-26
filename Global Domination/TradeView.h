#pragma once
#include "View.h"

#include "Nation.h"

namespace global_domination
{
	class TradeView : public View
	{
	public:
		TradeView::TradeView(Game* the_game, SDL_Window * parent, SDL_Rect client_area);
		virtual ~TradeView();
		void initialize();
		void respondToAction(TYPES::ACTION_LIST action);
	private:
		Nation nation_;
	};
}
