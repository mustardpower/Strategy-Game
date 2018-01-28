#pragma once

#include "SDLCompositePane.h"
#include "Game.h"
#include "SDLTabControl.h"

namespace global_domination
{
	class EndOfGameView : public SDLCompositePane
	{
	public:
		EndOfGameView::EndOfGameView(const GameModel& game_model, SDL_Window * parent, SDL_Rect client_area);
		virtual ~EndOfGameView();

		void initialize();
		void respondToAction(Sint32 action);

	private:
		const GameModel& game_model_;
	};
}