#include "NationSelectionView.h"

#include <memory>

#include "Action.h"
#include "ControlResources.h"
#include "NationSelectionViewModel.h"
#include "SDLButton.h"
#include "SDLMenu.h"
#include "SDLStaticText.h"

namespace global_domination
{
	NationSelectionView::NationSelectionView(Game* the_game, SDL_Window * parent, SDL_Rect client_area) : View(parent, client_area)
	{
		reciever_ = std::make_unique<NationSelectionViewModel>(the_game);

		nations_.push_back(Nation("Australia"));
		nations_.push_back(Nation("Germany"));
		nations_.push_back(Nation("Japan"));
		nations_.push_back(Nation("USA"));
	}

	NationSelectionView::~NationSelectionView()
	{
	}

	void NationSelectionView::initialize()
	{
		std::shared_ptr<SDLStaticText> prompt_label = std::make_shared<SDLStaticText>(parent_, "Select a nation:", client_area_.w * 0.15, client_area_.h * 0.25);
		addControl(prompt_label);

		std::shared_ptr<SDLStaticText> title_label = std::make_shared<SDLStaticText>(parent_, "GLOBAL DOMINATION", client_area_.w * 0.25, client_area_.h * 0.05);
		addControl(title_label);

		std::shared_ptr<SDLButton> start_button = std::make_shared<SDLButton>(parent_, "START", std::make_shared<ChangeViewAction>(reciever_, TYPES::ACTION_LIST::CHANGEVIEW_INBOX), client_area_.w * 0.8, client_area_.h * 0.8, 200, 300);
		addControl(start_button);

		std::shared_ptr<SDLMenu<Nation>> nation_selection_menu = std::make_shared<SDLMenu<Nation>>(parent_, client_area_.w * 0.2, client_area_.h * 0.4, client_area_.h * 0.1);
		nation_selection_menu->setId(NATION_SELECTION_MENU);

		// Share the same action between menu items
		std::shared_ptr<NationSelectionAction> nationSelectionAction = std::make_shared<NationSelectionAction>(reciever_);

		for (std::vector<Nation>::const_iterator nation = nations_.cbegin(); nation != nations_.end(); nation++)
		{
			std::string nationName = nation->reportString();
			nation_selection_menu->addMenuItem(MenuItem<Nation>(nationName, nationSelectionAction, *nation));
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
}
