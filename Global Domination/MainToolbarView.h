#pragma once
#include "SDLCompositePane.h"

namespace global_domination
{
	class Game;

	class MainToolbarView : public SDLCompositePane
	{
	public:
		MainToolbarView(Game* the_game, SDL_Window * parent, SDL_Rect client_area);
		void collapseMenus();
		bool handleClick(int x, int y);
		void initialize();
		void respondToAction(TYPES::ACTION_LIST action);
	private:
		Game* the_game_;
	};
}