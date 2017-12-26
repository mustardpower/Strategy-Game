#pragma once
#include "View.h"

namespace global_domination
{
	class RelationsView : public View
	{
	public:
		RelationsView::RelationsView(Game* the_game, SDL_Window * parent, SDL_Rect client_area);
		virtual ~RelationsView();
		void initialize();
		void respondToAction(TYPES::ACTION_LIST action);
	private:
		
	};
}
