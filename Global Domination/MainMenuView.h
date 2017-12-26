#pragma once
#include "SDLControl.h"

#include "Game.h"

namespace global_domination
{
	class MainMenuView : public SDLControl
	{
	public:
		MainMenuView(Game* the_game, SDL_Window* parent, SDL_Rect client_area);
		void initialize();
		void onKeyDown();
		void onKeyUp();
		void onKeyPress(int keyCode);
		void respondToAction(TYPES::ACTION_LIST action);
	private:
		Game* the_game_;
	};
}