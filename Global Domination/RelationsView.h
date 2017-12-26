#pragma once
#include "SDLCompositePane.h"

namespace global_domination
{
	class Game;

	class RelationsView : public SDLCompositePane
	{
	public:
		RelationsView::RelationsView(Game* the_game, SDL_Window * parent, SDL_Rect client_area);
		virtual ~RelationsView();
		void initialize();
		void respondToAction(TYPES::ACTION_LIST action);
	private:
		
	};
}
