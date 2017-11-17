#pragma once
#include "View.h"

namespace global_domination
{
	class MainMenuView : public View
	{
	public:
		MainMenuView(Game* the_game, SDL_Window* parent, SDL_Rect client_area);
		void initialize();
		void onKeyDown();
		void onKeyUp();
		void onKeyPress(int keyCode);
		void respondToAction(TYPES::ACTION_LIST action);
	};
}