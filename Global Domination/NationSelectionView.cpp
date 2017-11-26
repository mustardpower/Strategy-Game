#include "NationSelectionView.h"

#include <memory>

#include "Action.h"
#include "ControlResources.h"
#include "Game.h"
#include "SDLButton.h"
#include "SDLListBox.h"
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

	Nation* NationSelectionView::getSelectedNation()
	{
		std::shared_ptr<SDLListBox<Nation>> nation_selection_menu = std::dynamic_pointer_cast<SDLListBox<Nation>>(getControl(NATION_SELECTION_MENU));
		return nation_selection_menu->selectedItem();
	}

	void NationSelectionView::initialize()
	{
		addLabel("Select a nation:", client_area_.w * 0.15, client_area_.h * 0.25, NATION_SELECTION_PROMPT_LABEL);
		addLabel("", client_area_.w * 0.6, client_area_.h * 0.25, NATION_SELECTION_POPULATION_LABEL, 12);
		addLabel("", client_area_.w * 0.6, client_area_.h * 0.30, NATION_SELECTION_GDP_LABEL, 12);
		addLabel("", client_area_.w * 0.6, client_area_.h * 0.35, NATION_SELECTION_GDP_PER_CAPITA_LABEL, 12);

		std::shared_ptr<SDLButton> start_button = std::make_shared<SDLButton>(parent_, "START", std::make_shared<Action>(the_game_, TYPES::ACTION_LIST::CHANGEVIEW_INBOX), client_area_.w * 0.8, client_area_.h * 0.8, 200, 300);
		addControl(start_button);

		SDL_Rect menu_client_area { client_area_.w * 0.2, client_area_.h * 0.4, client_area_.w * 0.3, client_area_.h * 0.5 };
		std::shared_ptr<SDLListBox<Nation>> nation_selection_menu = std::make_shared<SDLListBox<Nation>>(parent_, menu_client_area, client_area_.h * 0.1);
		nation_selection_menu->setId(NATION_SELECTION_MENU);

		// Share the same action between menu items
		
		std::shared_ptr<Action> nationSelectionAction = std::make_shared<Action>(the_game_, TYPES::ACTION_LIST::SELECTING_NATION);

		for (std::vector<Nation>::const_iterator nation = nations_.cbegin(); nation != nations_.end(); nation++)
		{
			std::string nationName = nation->reportString();
			nation_selection_menu->addItem(ListItem<Nation>(nationName, nationSelectionAction, *nation));
		}	

		addControl(nation_selection_menu);

		updateSelectedNationDetails();
	}

	void NationSelectionView::onKeyDown()
	{
		std::shared_ptr<SDLListBox<Nation>> nation_selection_menu = std::dynamic_pointer_cast<SDLListBox<Nation>>(getControl(NATION_SELECTION_MENU));
		nation_selection_menu->nextItem();
	}

	void NationSelectionView::onKeyUp()
	{
		std::shared_ptr<SDLListBox<Nation>> nation_selection_menu = std::dynamic_pointer_cast<SDLListBox<Nation>>(getControl(NATION_SELECTION_MENU));
		nation_selection_menu->previousItem();
	}
	void NationSelectionView::onKeyPress(int keyCode)
	{
	}
	void NationSelectionView::respondToAction(TYPES::ACTION_LIST action)
	{
		// Only apply changes in this view once the game set up is confirmed
		switch(action)
		{
			case TYPES::ACTION_LIST::CHANGEVIEW_INBOX:
			{
				Nation* selected_nation = getSelectedNation();
				the_game_->getGameModel()->setSelectedNation(*selected_nation);

				Message welcome_message("Welcome to " + selected_nation->getName(), "You have arrived in " + selected_nation->getName() + ". Please wipe your feet and make our country glorious.");
				the_game_->getGameModel()->pushMessage(welcome_message);

				Message aMessage("Assistant Report", "I am your assistant. Have a look at these reports I have compiled for you.");
				the_game_->getGameModel()->pushMessage(aMessage);
			}
			break;
			case TYPES::ACTION_LIST::SELECTING_NATION:
			{
				updateSelectedNationDetails();
			}
			break;
		}
	}

	void NationSelectionView::updateSelectedNationDetails()
	{
		Nation* selected_nation = getSelectedNation();
		if (selected_nation)
		{
			setLabelText(NATION_SELECTION_POPULATION_LABEL, "Population: " + std::to_string(selected_nation->getPopulation()));
			setLabelText(NATION_SELECTION_GDP_LABEL, "GDP: " + std::to_string(selected_nation->getGDP()));
			setLabelText(NATION_SELECTION_GDP_PER_CAPITA_LABEL, "GDP per capita: " + std::to_string(selected_nation->getGDPPerCapita()));
		}
	}
}
