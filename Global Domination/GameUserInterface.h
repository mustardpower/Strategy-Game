#pragma once
#include "Action.h"

#include "SDL.h"

#include "View.h"

namespace global_domination {

	class Game;

	class GameUserInterface
	{
	public:
		SDL_Rect getClientArea() const;
		const int getWindowWidth();
		const int getWindowHeight();
		void initialize(Game* the_game);
		void render();
		void respondToAction(TYPES::ACTION_LIST action);
		void respondToMouseClick(TYPES::ACTION_LIST action, int x, int y);
		void switchActiveView(std::shared_ptr<View> view);
	private:
		Game* the_game_;
		const int kWindowWidth = 640;
		const int kWindowHeight = 480;
		std::shared_ptr<View> active_view_;
		SDL_Renderer *renderer_;
		SDL_Window* window_;
	};
}