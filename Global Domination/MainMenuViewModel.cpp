#include "MainMenuViewModel.h"
#include "Game.h"

namespace global_domination
{
	MainMenuViewModel::MainMenuViewModel(Game* the_game) : ViewModel(the_game)
	{

	}

	void MainMenuViewModel::setAction(TYPES::ACTION_LIST action)
	{
		switch (action)
		{
			case TYPES::ACTION_LIST::CHANGEVIEW_NATIONSELECTION:
			{
				the_game_->relayAction(action);
			}
			case TYPES::ACTION_LIST::QUIT:
			{
				SDL_Event quit_event;
				quit_event.type = SDL_QUIT;
				SDL_PushEvent(&quit_event);
			}
		}
	}
}
