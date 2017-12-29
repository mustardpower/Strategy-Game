#pragma once
#include "SDLCompositePane.h"

namespace global_domination
{
	class GameModel;

	class MainToolbarView : public SDLCompositePane
	{
	public:
		MainToolbarView(std::shared_ptr<GameModel> the_model, SDL_Window * parent, SDL_Rect client_area);
		void collapseUnclickedMenus(int x, int y);
		bool handleClick(int x, int y);
		void initialize();
		void respondToAction(Sint32 action);
	private:
		std::shared_ptr<GameModel> game_model_;
	};
}