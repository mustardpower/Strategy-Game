#include "MainToolbarView.h"

#include "Action.h"
#include "ColorPreferences.h"
#include "GameModel.h"
#include "ListItem.h"
#include "SDLButton.h"
#include "SDLDropDownMenu.h"

namespace global_domination
{
	MainToolbarView::MainToolbarView(std::shared_ptr<GameModel> the_model, SDL_Window * parent, SDL_Rect client_area) : SDLCompositePane(parent, client_area)
	{
		game_model_ = the_model;
		useSecondaryColorScheme();
	}

	void MainToolbarView::collapseUnclickedMenus(int x, int y)
	{
		std::shared_ptr<SDLDropDownMenu<int>> home_menu = std::dynamic_pointer_cast<SDLDropDownMenu<int>>(getChildControl(TOOLBAR_MENU_HOME));
		home_menu->collapseIfNotClicked(x, y);

		std::shared_ptr<SDLDropDownMenu<int>> settings_menu = std::dynamic_pointer_cast<SDLDropDownMenu<int>>(getChildControl(TOOLBAR_MENU_SETTINGS));
		settings_menu->collapseIfNotClicked(x, y);
	}

	bool MainToolbarView::handleClick(int x, int y)
	{
		if (is_visible_)
		{
			collapseUnclickedMenus(x, y);
			SDLCompositePane::handleClick(x, y);
		}

		return false;
	}

	void MainToolbarView::initialize()
	{
		addLabel(game_model_->getDateString(), (int)(client_area_.w * 0.05), (int)(client_area_.h * 0.4), TOOLBAR_DATE_LABEL, 18, true);
		
		std::shared_ptr<SDLDropDownMenu<int>> home_menu = std::make_shared<SDLDropDownMenu<int>>(parent_, (int)(client_area_.w * 0.4), (int)(client_area_.h * 0.4), (int)(client_area_.w * 0.4), client_area_.h, (int)(client_area_.h * 0.4));
		home_menu->addMenuItem(ListItem<int>("HOME", nullptr, 0));
		home_menu->addMenuItem(ListItem<int>("INBOX", std::make_shared<Action>(TYPES::ACTION_LIST::CHANGEVIEW_INBOX), 1));
		home_menu->addMenuItem(ListItem<int>("FINANCES", std::make_shared<Action>(TYPES::ACTION_LIST::CHANGEVIEW_FINANCES), 2));
		home_menu->addMenuItem(ListItem<int>("TRADE", std::make_shared<Action>(TYPES::ACTION_LIST::CHANGEVIEW_TRADE), 3));
		home_menu->addMenuItem(ListItem<int>("RELATIONS", std::make_shared<Action>(TYPES::ACTION_LIST::CHANGEVIEW_RELATIONS), 4));
		home_menu->addMenuItem(ListItem<int>("WORLD", std::make_shared<Action>(TYPES::ACTION_LIST::CHANGEVIEW_WORLD), 5));
		home_menu->setId(TOOLBAR_MENU_HOME);
		home_menu->useSecondaryColorScheme();
		addChildControl(home_menu);

		std::shared_ptr<SDLDropDownMenu<int>> settings_menu = std::make_shared<SDLDropDownMenu<int>>(parent_, (int)(client_area_.w * 0.6), (int)(client_area_.h * 0.4), (int)(client_area_.w * 0.6), client_area_.h, (int)(client_area_.h * 0.4));
		settings_menu->addMenuItem(ListItem<int>("SETTINGS", nullptr, 0));
		settings_menu->addMenuItem(ListItem<int>("QUIT", std::make_shared<Action>(TYPES::ACTION_LIST::QUIT), 1));
		settings_menu->setId(TOOLBAR_MENU_SETTINGS);
		settings_menu->useSecondaryColorScheme();
		addChildControl(settings_menu);

		SDL_Rect next_button_client_area{ (int)(client_area_.w * 0.8), (int)(client_area_.h * 0.4), 200, (int)(client_area_.h * 0.4) };
		std::shared_ptr<SDLButton> next_button = std::make_shared<SDLButton>(parent_, "NEXT", std::make_shared<Action>(TYPES::ACTION_LIST::NEXT_TURN), next_button_client_area);
		next_button->useSecondaryColorScheme();
		addChildControl(next_button);
	}

	void MainToolbarView::respondToAction(Sint32 action)
	{
		switch (action)
		{
			case TYPES::ACTION_LIST::NEXT_TURN:
			{
				setLabelText(TOOLBAR_DATE_LABEL, game_model_->getDateString());
			}
			break;
		}
	}
}
