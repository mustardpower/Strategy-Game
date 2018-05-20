#pragma once
#include "SDLCompositePane.h"

namespace global_domination
{
	class GameModel;

	class WorldView : public SDLCompositePane
	{
	public:
		WorldView(GameModel& game_model, SDL_Window * parent, SDL_Rect client_area);
		virtual ~WorldView();
		void initialize();
		void respondToAction(Sint32 action);
	private:
		GameModel& game_model_;
	};
}
