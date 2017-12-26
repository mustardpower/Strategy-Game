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

	void MainToolbarView::collapseMenus()
	{
		std::shared_ptr<SDLDropDownMenu<int>> home_menu = std::dynamic_pointer_cast<SDLDropDownMenu<int>>(getControl(TOOLBAR_MENU_HOME));
		home_menu->collapseMenu();

		std::shared_ptr<SDLDropDownMenu<int>> settings_menu = std::dynamic_pointer_cast<SDLDropDownMenu<int>>(getControl(TOOLBAR_MENU_SETTINGS));
		settings_menu->collapseMenu();

	}

	SDL_Color MainToolbarView::getBackgroundColor()
	{
		return ColorPreferences::getSecondaryBackgroundColor();
	}

	bool MainToolbarView::handleClick(int x, int y)
	{
		if (isVisible_)
		{
			collapseMenus();
			View::handleClick(x, y);
		}

		return false;
	}

	void MainToolbarView::initialize()
	{
		addLabel(the_game_->getGameModel()->getDateString(), client_area_.w * 0.05, client_area_.h * 0.4, TOOLBAR_DATE_LABEL, 18, true);
		
		std::shared_ptr<SDLDropDownMenu<int>> home_menu = std::make_shared<SDLDropDownMenu<int>>(parent_, client_area_.w * 0.4, client_area_.h * 0.4, client_area_.w * 0.4, client_area_.h, client_area_.h * 0.4);
		home_menu->addMenuItem(ListItem<int>("HOME", nullptr, 0));
		home_menu->addMenuItem(ListItem<int>("INBOX", std::make_shared<Action>(the_game_, TYPES::ACTION_LIST::CHANGEVIEW_INBOX), 1));
		home_menu->addMenuItem(ListItem<int>("FINANCES", std::make_shared<Action>(the_game_, TYPES::ACTION_LIST::CHANGEVIEW_FINANCES), 2));
		home_menu->addMenuItem(ListItem<int>("TRADE", std::make_shared<Action>(the_game_, TYPES::ACTION_LIST::CHANGEVIEW_TRADE), 3));
		home_menu->addMenuItem(ListItem<int>("RELATIONS", std::make_shared<Action>(the_game_, TYPES::ACTION_LIST::CHANGEVIEW_RELATIONS), 3));
		home_menu->setId(TOOLBAR_MENU_HOME);
		home_menu->useSecondaryColorScheme();
		addControl(home_menu);

		std::shared_ptr<SDLDropDownMenu<int>> settings_menu = std::make_shared<SDLDropDownMenu<int>>(parent_, client_area_.w * 0.7, client_area_.h * 0.4, client_area_.w * 0.7, client_area_.h, client_area_.h * 0.4);
		settings_menu->addMenuItem(ListItem<int>("SETTINGS", nullptr, 0));
		settings_menu->addMenuItem(ListItem<int>("QUIT", std::make_shared<Action>(the_game_, TYPES::ACTION_LIST::QUIT), 1));
		settings_menu->setId(TOOLBAR_MENU_SETTINGS);
		settings_menu->useSecondaryColorScheme();
		addControl(settings_menu);

		std::shared_ptr<SDLButton> next_button = std::make_shared<SDLButton>(parent_, "NEXT", std::make_shared<Action>(the_game_, TYPES::ACTION_LIST::NEXT_TURN), client_area_.w * 0.9, client_area_.h * 0.4, 200, 300);
		next_button->useSecondaryColorScheme();
		addControl(next_button);
	}

	void MainToolbarView::respondToAction(TYPES::ACTION_LIST action)
	{
		switch (action)
		{
			case TYPES::ACTION_LIST::NEXT_TURN:
			{
				setLabelText(TOOLBAR_DATE_LABEL, the_game_->getGameModel()->getDateString());
			}
			break;
		}
	}
}
