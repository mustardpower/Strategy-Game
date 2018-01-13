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
	NationSelectionView::NationSelectionView(std::shared_ptr<GameModel> the_model, SDL_Window * parent, SDL_Rect client_area) : SDLCompositePane(parent, client_area)
	{
		game_model_ = the_model;
		NationFactory nationFactory;
		nationFactory.createNations("nations.json");
		nations_ = nationFactory.getNations();
		the_model->setNations(nations_);
		the_model->setNationalRelationships();
	}

	NationSelectionView::~NationSelectionView()
	{
	}

	Nation* NationSelectionView::getSelectedNation()
	{
		std::shared_ptr<SDLListBox<Nation>> nation_selection_menu = std::dynamic_pointer_cast<SDLListBox<Nation>>(getChildControl(NATION_SELECTION_MENU));
		std::string nation_name = nation_selection_menu->selectedItem()->getName();
		return game_model_->getNation(nation_name);
		
	}

	void NationSelectionView::initialize()
	{
		addLabel("Select a nation:", (int)(client_area_.w * 0.15), (int)(client_area_.h * 0.25), NATION_SELECTION_PROMPT_LABEL);
		addLabel("", (int)(client_area_.w * 0.6), (int)(client_area_.h * 0.25), NATION_SELECTION_POPULATION_LABEL, 15);
		addLabel("", (int)(client_area_.w * 0.6), (int)(client_area_.h * 0.30), NATION_SELECTION_GDP_LABEL, 15);
		addLabel("", (int)(client_area_.w * 0.6), (int)(client_area_.h * 0.35), NATION_SELECTION_GDP_PER_CAPITA_LABEL, 15);

		SDL_Rect start_button_client_area{ (int)(client_area_.w * 0.8), (int)(client_area_.h * 0.8), (int)(client_area_.w * 0.1), (int)(client_area_.h * 0.05) };
		std::shared_ptr<SDLButton> start_button = std::make_shared<SDLButton>(
			parent_,
			"START",
			std::make_shared<Action>(TYPES::ACTION_LIST::CHANGEVIEW_INBOX),
			start_button_client_area
			);

		addChildControl(start_button);

		SDL_Rect menu_client_area { (int)(client_area_.w * 0.2), (int)(client_area_.h * 0.4), (int)(client_area_.w * 0.3), (int)(client_area_.h * 0.5) };
		std::shared_ptr<SDLListBox<Nation>> nation_selection_menu = std::make_shared<SDLListBox<Nation>>(parent_, menu_client_area);
		nation_selection_menu->setId(NATION_SELECTION_MENU);

		// Share the same action between menu items
		
		std::shared_ptr<Action> nationSelectionAction = std::make_shared<Action>(TYPES::ACTION_LIST::SELECTING_NATION);

		for (std::vector<Nation>::const_iterator nation = nations_.cbegin(); nation != nations_.end(); nation++)
		{
			std::string nationName = nation->reportString();
			nation_selection_menu->addItem(ListItem<Nation>(nationName, nationSelectionAction, *nation));
		}	

		addChildControl(nation_selection_menu);

		updateSelectedNationDetails();
	}

	void NationSelectionView::onKeyDown()
	{
		std::shared_ptr<SDLListBox<Nation>> nation_selection_menu = std::dynamic_pointer_cast<SDLListBox<Nation>>(getChildControl(NATION_SELECTION_MENU));
		nation_selection_menu->nextItem();
	}

	void NationSelectionView::onKeyUp()
	{
		std::shared_ptr<SDLListBox<Nation>> nation_selection_menu = std::dynamic_pointer_cast<SDLListBox<Nation>>(getChildControl(NATION_SELECTION_MENU));
		nation_selection_menu->previousItem();
	}
	
	void NationSelectionView::respondToAction(Sint32 action)
	{
		// Only apply changes in this view once the game set up is confirmed
		switch(action)
		{
			case TYPES::ACTION_LIST::CHANGEVIEW_INBOX:
			{
				Nation* selected_nation = getSelectedNation();
				game_model_->setSelectedNation(selected_nation);

				Message welcome_message("Welcome to " + selected_nation->getName(), "You have arrived in " + selected_nation->getName() + ". Please wipe your feet and make our country glorious.");
				game_model_->pushMessage(welcome_message);

				Message aMessage("Assistant Report", "I am your assistant. Have a look at these reports I have compiled for you.");
				game_model_->pushMessage(aMessage);
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
			setLabelText(NATION_SELECTION_GDP_LABEL, "Balance: " + std::to_string(selected_nation->getBalance()));
			setLabelText(NATION_SELECTION_GDP_PER_CAPITA_LABEL, "Balance per capita: " + std::to_string(selected_nation->getBalancePerCapita()));
		}
	}
}
