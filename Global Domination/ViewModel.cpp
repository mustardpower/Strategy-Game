#include "ViewModel.h"
#include "Game.h"

namespace global_domination
{

	ViewModel::ViewModel(Game* the_game)
	{
		the_game_ = the_game;
	}

	void ViewModel::setAction(TYPES::ACTION_LIST action)
	{
		the_game_->relayAction(action);
	}

	void ViewModel::applyTo(GameModel gameModel)
	{
	}
}
