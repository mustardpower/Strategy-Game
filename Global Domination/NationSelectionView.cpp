#include "NationSelectionView.h"

#include <memory>

#include "Action.h"
#include "SDLButton.h"
#include "SDLMenu.h"
#include "SDLStaticText.h"

namespace global_domination
{
	NationSelectionView::NationSelectionView(IReciever * reciever, SDL_Window * parent, SDL_Rect client_area) : View(reciever, parent, client_area)
	{
		nations_.push_back(Nation("Australia"));
		nations_.push_back(Nation("Germany"));
		nations_.push_back(Nation("Japan"));
		nations_.push_back(Nation("USA"));
	}

	void NationSelectionView::initialize()
	{
		std::shared_ptr<SDLStaticText> prompt_label = std::make_shared<SDLStaticText>(parent_, "Select a nation:", client_area_.w * 0.15, client_area_.h * 0.25);
		addControl(prompt_label);

		std::shared_ptr<SDLStaticText> title_label = std::make_shared<SDLStaticText>(parent_, "GLOBAL DOMINATION", client_area_.w * 0.25, client_area_.h * 0.05);
		addControl(title_label);

		std::shared_ptr<SDLButton> start_button = std::make_shared<SDLButton>(parent_, "START", std::make_shared<OpenInboxAction>(reciever_), client_area_.w * 0.8, client_area_.h * 0.8, 200, 300);
		addControl(start_button);

		std::shared_ptr<SDLMenu<Nation>> nation_selection_menu = std::make_shared<SDLMenu<Nation>>(parent_, client_area_.w * 0.2, client_area_.h * 0.4, client_area_.h * 0.1);
		for (std::vector<Nation>::const_iterator nation = nations_.cbegin(); nation != nations_.end(); nation++)
		{
			std::shared_ptr<NationSelectionAction> nationSelectionAction = std::make_shared<NationSelectionAction>(reciever_);
			std::string nationName = nation->reportString();
			nation_selection_menu->addMenuItem(MenuItem<Nation>(nationName, nationSelectionAction, *nation));
		}

		addControl(nation_selection_menu);
	}
}
