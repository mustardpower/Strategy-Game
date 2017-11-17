#pragma once

#include "ViewModel.h"

namespace global_domination
{
	class Game;

	class NationSelectionViewModel : public ViewModel
	{
	public:
		NationSelectionViewModel(Game* the_game);
		void setAction(TYPES::ACTION_LIST action);
	};
}