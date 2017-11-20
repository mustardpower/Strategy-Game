#include "NationSelectionView.h"

#include <memory>

#include "Action.h"
#include "ControlResources.h"
#include "Game.h"
#include "SDLButton.h"
#include "SDLMenu.h"
#include "SDLStaticText.h"

#include "NationFactory.h"

namespace global_domination
{
	NationSelectionView::NationSelectionView(Game* the_game, SDL_Window * parent, SDL_Rect client_area) : View(the_game, parent, client_area)
	{
		NationFactory nationFactory;
		nations_ = nationFactory.createNations("nations.json");
	}

	NationSelectionView::~NationSelectionView()
	{
	}

	void NationSelectionView::initialize()
	{
		std::shared_ptr<SDLStaticText> prompt_label = std::make_shared<SDLStaticText>(parent_, "Select a nation:", client_area_.w * 0.15, client_area_.h * 0.25, background_color_);
		addControl(prompt_label);

		std::shared_ptr<SDLButton> start_button = std::make_shared<SDLButton>(parent_, "START", std::make_shared<Action>(the_game_, TYPES::ACTION_LIST::CHANGEVIEW_INBOX), client_area_.w * 0.8, client_area_.h * 0.8, 200, 300, background_color_);
		addControl(start_button);

		std::shared_ptr<SDLMenu<Nation>> nation_selection_menu = std::make_shared<SDLMenu<Nation>>(parent_, client_area_.w * 0.2, client_area_.h * 0.4, client_area_.h * 0.1, background_color_);
		nation_selection_menu->setId(NATION_SELECTION_MENU);

		// Share the same action between menu items
		
		std::shared_ptr<Action> nationSelectionAction = std::make_shared<Action>(the_game_, TYPES::ACTION_LIST::SELECTING_NATION);

		for (std::vector<Nation>::const_iterator nation = nations_.cbegin(); nation != nations_.end(); nation++)
		{
			std::string nationName = nation->reportString();
			nation_selection_menu->addMenuItem(ListItem<Nation>(nationName, nationSelectionAction, *nation));
		}	

		addControl(nation_selection_menu);
	}

	void NationSelectionView::onKeyDown()
	{
		std::shared_ptr<SDLMenu<Nation>> nation_selection_menu = std::dynamic_pointer_cast<SDLMenu<Nation>>(getControl(NATION_SELECTION_MENU));
		nation_selection_menu->nextMenuItem();
	}

	void NationSelectionView::onKeyUp()
	{
		std::shared_ptr<SDLMenu<Nation>> nation_selection_menu = std::dynamic_pointer_cast<SDLMenu<Nation>>(getControl(NATION_SELECTION_MENU));
		nation_selection_menu->previousMenuItem();
	}
	void NationSelectionView::onKeyPress(int keyCode)
	{
	}
	void NationSelectionView::respondToAction(TYPES::ACTION_LIST action)
	{
		// Only apply changes in this view once the game set up is confirmed
		if (action == TYPES::ACTION_LIST::CHANGEVIEW_INBOX)
		{
			std::shared_ptr<SDLMenu<Nation>> nation_selection_menu = std::dynamic_pointer_cast<SDLMenu<Nation>>(getControl(NATION_SELECTION_MENU));
			Nation* selected_nation = nation_selection_menu->selectedItem();
			the_game_->getGameModel()->setSelectedNation(*selected_nation);
		}
	}
}
