#pragma once
#include "Action.h"
#include "View.h"

namespace global_domination
{
	class MainMenuView : public View
	{
	public:
		MainMenuView(std::shared_ptr<IReciever> reciever, SDL_Window* parent, SDL_Rect client_area);
		void initialize();
		void onKeyDown();
	};
}