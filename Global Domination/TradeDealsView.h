#pragma once

#include "SDLControl.h"

namespace global_domination
{
	class Game;
	class TradeDealsView : public SDLControl
	{
	public:
		TradeDealsView(Game* the_game, SDL_Window * parent, SDL_Rect client_area);
		void initialize();
		void respondToAction(TYPES::ACTION_LIST action);

	private:
	};
}