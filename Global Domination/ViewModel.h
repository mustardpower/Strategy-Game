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
		virtual void setAction(TYPES::ACTION_LIST action) = 0;
		void applyTo(GameModel gameModel);

	protected:
		Game* the_game_;
	};
}