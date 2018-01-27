#include "NationSelectionView.h"

#include <memory>

#include "Action.h"
#include "ControlResources.h"
#include "Game.h"
#include "SDLButton.h"
#include "SDLDropDownList.h"
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

		std::vector<Nation*> nation_ptrs;
		for (std::vector<Nation>::iterator nation = nations_.begin(); nation != nations_.end(); nation++)
		{
			nation_ptrs.push_back(new Nation(*nation));
		}

		the_model->setNations(nation_ptrs);
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

	int NationSelectionView::getSelectedNumberOfTurns()
	{
		std::shared_ptr<SDLDropDownList> game_turns_dropdown = std::dynamic_pointer_cast<SDLDropDownList>(getChildControl(GAME_TURNS_DROPDOWN_LIST));
		return stoi(game_turns_dropdown->getText());

	}

	void NationSelectionView::addGameTurnsDropDownList()
	{
		addLabel("Game turns:", (int)(client_area_.w * 0.7), (int)(client_area_.h * 0.14), NATION_SELECTION_GAMETURNS_LABEL, 16);
		SDL_Rect tax_dropdown_client_area{ (int)(client_area_.w * 0.81), (int)(client_area_.h * 0.13), (int)(client_area_.w * 0.18), (int)(client_area_.h * 0.04) };
		std::shared_ptr<SDLDropDownList> game_turns_drop_down_list = std::make_shared<SDLDropDownList>(parent_, tax_dropdown_client_area);
		game_turns_drop_down_list->setFontSize(16);
		std::vector<std::string> items{ "100", "200", "300", "400" };
		game_turns_drop_down_list->setItems(items);
		game_turns_drop_down_list->setId(GAME_TURNS_DROPDOWN_LIST);
		game_turns_drop_down_list->setText(items.at(0));
		addChildControl(game_turns_drop_down_list);
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

		addGameTurnsDropDownList();

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

				const int kNumberOfTurns = getSelectedNumberOfTurns();
				game_model_->setNumberOfTurns(kNumberOfTurns);

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
			setLabelText(NATION_SELECTION_GDP_LABEL, "Balance: " + selected_nation->reportBalance());
			setLabelText(NATION_SELECTION_GDP_PER_CAPITA_LABEL, "Balance per capita: " + selected_nation->reportBalancePerCapita());
		}
	}
}
