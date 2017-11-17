#pragma once
#include "Action.h"
#include "GameModel.h"

namespace global_domination
{
	class Game;

	class ViewModel : public IReciever
	{
	public:
		ViewModel(Game* the_game);
		void setAction(TYPES::ACTION_LIST action);
		void applyTo(GameModel gameModel);

	protected:
		Game* the_game_;
	};
}