#pragma once
#include "SDLCompositePane.h"

namespace global_domination
{
	class MainMenuView : public SDLCompositePane
	{
	public:
		MainMenuView(SDL_Window* parent, SDL_Rect client_area);
		void initialize();
		void onKeyDown();
		void onKeyUp();
		void onKeyPress(int keyCode);
		void respondToAction(Sint32 action);
	};
}