#include "MainMenuView.h"

#include <memory>

#include "SDL.h"

#include "Action.h"
#include "Game.h"
#include "MenuItem.h"
#include "SDLMenu.h"

namespace global_domination
{
	MainMenuView::MainMenuView(IReciever * reciever, SDL_Window * parent, SDL_Rect client_area) : View(reciever, parent, client_area)
	{

	}

	void MainMenuView::initialize()
	{
		std::shared_ptr<SDLMenu<int>> main_menu_ = std::make_shared<SDLMenu<int>>(parent_, client_area_.w * 0.2, client_area_.h * 0.3, client_area_.h * 0.1);
		main_menu_->addMenuItem(MenuItem<int>("PLAY!", std::make_shared<StartGameAction>(reciever_), 0));
		main_menu_->addMenuItem(MenuItem<int>("QUIT!", std::make_shared<QuitGameAction>(reciever_), 1));
		addControl(main_menu_);
	}
}
