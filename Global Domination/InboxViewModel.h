#pragma once

#include "ViewModel.h"

namespace global_domination
{
	class InboxViewModel : public ViewModel
	{
	public:
		InboxViewModel(Game* the_game);
		void setAction(TYPES::ACTION_LIST action);
	};
}