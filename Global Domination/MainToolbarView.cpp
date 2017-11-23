#include "MainToolbarView.h"

#include "Action.h"
#include "ColorPreferences.h"
#include "Game.h"
#include "ListItem.h"
#include "SDLButton.h"
#include "SDLDropDownMenu.h"

namespace global_domination
{
	MainToolbarView::MainToolbarView(Game* the_game, SDL_Window * parent, SDL_Rect client_area) : View(the_game, parent, client_area)
	{
	}

	SDL_Color MainToolbarView::getBackgroundColor()
	{
		return ColorPreferences::getSecondaryBackgroundColor();
	}

	void MainToolbarView::initialize()
	{
		std::shared_ptr<SDLDropDownMenu<int>> settings_menu = std::make_shared<SDLDropDownMenu<int>>(parent_, client_area_.w * 0.7, client_area_.h * 0.4, client_area_.h * 0.4);
		settings_menu->addMenuItem(ListItem<int>("SETTINGS", std::make_shared<Action>(the_game_, TYPES::ACTION_LIST::OPEN_MENU), 0));
		settings_menu->addMenuItem(ListItem<int>("QUIT", std::make_shared<Action>(the_game_, TYPES::ACTION_LIST::QUIT), 1));
		settings_menu->useSecondaryColorScheme();
		addControl(settings_menu);

		std::shared_ptr<SDLButton> next_button = std::make_shared<SDLButton>(parent_, "NEXT", std::make_shared<Action>(the_game_, TYPES::ACTION_LIST::NEXT_TURN), client_area_.w * 0.9, client_area_.h * 0.4, 200, 300);
		next_button->useSecondaryColorScheme();
		addControl(next_button);
	}

	void MainToolbarView::respondToAction(TYPES::ACTION_LIST action)
	{

	}
}
