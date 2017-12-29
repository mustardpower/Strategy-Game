#pragma once

#include "SDLCompositePane.h"
#include "Game.h"
#include "Nation.h"

namespace global_domination
{
	class FinancesView : public SDLCompositePane
	{
	public:
		FinancesView::FinancesView(std::shared_ptr<GameModel>, SDL_Window * parent, SDL_Rect client_area);
		virtual ~FinancesView();
		void initialize();
		void respondToAction(Sint32 action);
	private:
		Nation* nation_;
	};
}