#include "NationSelectionViewModel.h"

#include "Game.h"

namespace global_domination
{
	NationSelectionViewModel::NationSelectionViewModel(Game * the_game) : ViewModel(the_game)
	{
	}

	void NationSelectionViewModel::setAction(TYPES::ACTION_LIST action)
	{
		switch (action)
		{
			case TYPES::ACTION_LIST::CHANGEVIEW_INBOX:
			{
				the_game_->relayAction(action);
			}
		}
	}
}
