#include "MainMenuView.h"

#include <memory>

#include "SDL.h"

#include "Action.h"
#include "Game.h"
#include "ListItem.h"
#include "SDLMenu.h"

namespace global_domination
{
	MainMenuView::MainMenuView(SDL_Window * parent, SDL_Rect client_area) : SDLCompositePane(parent, client_area)
	{
	}

	void MainMenuView::initialize()
	{
		std::shared_ptr<SDLMenu<int>> main_menu = std::make_shared<SDLMenu<int>>(parent_, (int)(client_area_.w * 0.2), (int)(client_area_.h * 0.3), (int)(client_area_.h * 0.1));
		main_menu->addMenuItem(ListItem<int>("PLAY!", std::make_shared<Action>(TYPES::ACTION_LIST::CHANGEVIEW_NATIONSELECTION), 0));
		main_menu->addMenuItem(ListItem<int>("QUIT!", std::make_shared<Action>(TYPES::ACTION_LIST::QUIT), 1));
		addChildControl(main_menu);
		main_menu->setId(MAIN_MENU);
	}
	
	void MainMenuView::onKeyDown()
	{
		std::shared_ptr<SDLMenu<int>> main_menu = std::dynamic_pointer_cast<SDLMenu<int>>(getChildControl(MAIN_MENU));
		main_menu->nextMenuItem();
	}

	void MainMenuView::onKeyUp()
	{
		std::shared_ptr<SDLMenu<int>> main_menu = std::dynamic_pointer_cast<SDLMenu<int>>(getChildControl(MAIN_MENU));
		main_menu->nextMenuItem();
	}
	void MainMenuView::onKeyPress(int keyCode)
	{
		switch (keyCode)
		{
			case SDLK_RETURN: 
			{
				std::shared_ptr<SDLMenu<int>> main_menu = std::dynamic_pointer_cast<SDLMenu<int>>(getChildControl(MAIN_MENU));
				main_menu->selectCurrentItem();
			}
			break;
		}
	}
	void MainMenuView::respondToAction(Sint32 action)
	{
		switch (action)
		{
			case TYPES::ACTION_LIST::KEYPRESS_UP:
			{
				onKeyUp();
			}
			break;
			case TYPES::ACTION_LIST::KEYPRESS_DOWN:
			{
				onKeyDown();
			}
			break;
			case TYPES::ACTION_LIST::KEYPRESS_RETURN:
			{
				onKeyPress(SDLK_RETURN);
			}
			break;
		}
	}
}
