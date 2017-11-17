#pragma once

#include "ViewModel.h"

namespace global_domination
{
	class MainMenuViewModel : public ViewModel
	{
	public:
		MainMenuViewModel(Game* the_game);
		void setAction(TYPES::ACTION_LIST action);
	};
}