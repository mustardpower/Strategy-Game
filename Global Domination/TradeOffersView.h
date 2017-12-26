#pragma once

#include "SDLControl.h"

#include "Nation.h"

namespace global_domination
{
	class Game;
	class TradeOffersView : public SDLControl
	{
	public:
		TradeOffersView(Game* the_game, SDL_Window * parent, SDL_Rect client_area);
		void initialize();
		void respondToAction(TYPES::ACTION_LIST action);
		
	private:
	};
}