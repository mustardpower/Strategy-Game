#pragma once
#include "View.h"

namespace global_domination
{
	class MainToolbarView : public View
	{
	public:
		MainToolbarView::MainToolbarView(Game* the_game, SDL_Window * parent, SDL_Rect client_area);
		void collapseMenus();
		SDL_Color getBackgroundColor();
		bool handleClick(int x, int y);
		void initialize();
		void respondToAction(TYPES::ACTION_LIST action);
	};
}