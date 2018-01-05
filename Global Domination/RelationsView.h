#pragma once
#include "SDLCompositePane.h"

namespace global_domination
{
	class GameModel;

	class RelationsView : public SDLCompositePane
	{
	public:
		RelationsView::RelationsView(std::shared_ptr<GameModel> game_model, SDL_Window * parent, SDL_Rect client_area);
		virtual ~RelationsView();
		void initialize();
		void respondToAction(Sint32 action);
	private:
		std::shared_ptr<GameModel> game_model_;
	};
}
