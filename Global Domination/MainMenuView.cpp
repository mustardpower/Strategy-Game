#include "MainMenuView.h"

#include <memory>

#include "SDL.h"

#include "Action.h"
#include "Game.h"
#include "MenuItem.h"
#include "SDLMenu.h"

namespace global_domination
{
	MainMenuView::MainMenuView(std::shared_ptr<IReciever> reciever, SDL_Window * parent, SDL_Rect client_area) : View(reciever, parent, client_area)
	{

	}

	void MainMenuView::initialize()
	{
		std::shared_ptr<SDLMenu<int>> main_menu = std::make_shared<SDLMenu<int>>(parent_, client_area_.w * 0.2, client_area_.h * 0.3, client_area_.h * 0.1);
		main_menu->addMenuItem(MenuItem<int>("PLAY!", std::make_shared<ChangeViewAction>(reciever_, TYPES::ACTION_LIST::NATION_SELECTION), 0));
		main_menu->addMenuItem(MenuItem<int>("QUIT!", std::make_shared<QuitGameAction>(reciever_), 1));
		addControl(main_menu);
		main_menu->setId(MAIN_MENU);
	}
	
	void MainMenuView::onKeyDown()
	{
		std::shared_ptr<SDLMenu<int>> main_menu = std::dynamic_pointer_cast<SDLMenu<int>>(getControl(MAIN_MENU));
		main_menu->nextMenuItem();
	}

	void MainMenuView::onKeyUp()
	{
		std::shared_ptr<SDLMenu<int>> main_menu = std::dynamic_pointer_cast<SDLMenu<int>>(getControl(MAIN_MENU));
		main_menu->nextMenuItem();
	}
	void MainMenuView::onKeyPress(int keyCode)
	{
		switch (keyCode)
		{
			case SDLK_RETURN: 
			{
				std::shared_ptr<SDLMenu<int>> main_menu = std::dynamic_pointer_cast<SDLMenu<int>>(getControl(MAIN_MENU));
				main_menu->selectCurrentItem();
			}
			break;
		}
	}
}
