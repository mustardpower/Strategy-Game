#pragma once
#include "Action.h"

#include "SDL.h"

#include "MainToolbarView.h"
#include "SDLCompositePane.h"

namespace global_domination {

	class Game;

	class GameUserInterface
	{
	public:
		GameUserInterface();
		SDL_Rect getClientArea() const;
		void initialize(Game* the_game);
		bool isQuiting();
		void render();
		void respondToAction(TYPES::ACTION_LIST action);
		void respondToMouseClick(TYPES::ACTION_LIST action, int x, int y);
		void switchActiveControl(std::shared_ptr<SDLCompositePane> top_control);
		void update();
	private:
		bool is_quiting_;
		Game* the_game_;
		std::unique_ptr<MainToolbarView> toolbar_;
		std::shared_ptr<SDLCompositePane> active_control_;
		SDL_Renderer *renderer_;
		SDL_Window* window_;
	};
}