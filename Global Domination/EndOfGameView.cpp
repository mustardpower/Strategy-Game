#include "EndOfGameView.h"

namespace global_domination
{
	EndOfGameView::EndOfGameView(const GameModel & game_model, SDL_Window * parent, SDL_Rect client_area) : SDLCompositePane(parent, client_area), game_model_(game_model)
	{
	}

	EndOfGameView::~EndOfGameView()
	{
	}

	void EndOfGameView::initialize()
	{
	}

	void EndOfGameView::respondToAction(Sint32 action)
	{
	}
}

