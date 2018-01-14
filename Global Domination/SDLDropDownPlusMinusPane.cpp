#include "SDLDropDownPlusMinusPane.h"

#include "SDLButton.h"
#include "SDLDropDownList.h"

namespace global_domination
{
	SDLDropDownPlusMinusPane::SDLDropDownPlusMinusPane(SDL_Window * parent, SDL_Rect client_area) : SDLCompositePane(parent, client_area)
	{
		initialize();
	}

	void SDLDropDownPlusMinusPane::initialize()
	{
		SDL_Rect tax_dropdown_client_area{ client_area_.x, client_area_.y, (int)(client_area_.w * 0.8), client_area_.h };
		std::shared_ptr<SDLDropDownList> tax_drop_down_list = std::make_shared<SDLDropDownList>(parent_, tax_dropdown_client_area);
		tax_drop_down_list->setFontSize(16);
		std::vector<std::string> items{ "0%", "5%", "10%", "15%", "20%" };
		tax_drop_down_list->setItems(items);
		addChildControl(tax_drop_down_list);

		SDL_Rect minus_button_client_area{ client_area_.x + tax_dropdown_client_area.w, client_area_.y, (int)(client_area_.w * 0.1), client_area_.h };
		std::shared_ptr<Action> minus_action = std::make_shared<Action>();
		std::shared_ptr<SDLButton> minus_button = std::make_shared<SDLButton>(parent_,"-", minus_action, minus_button_client_area);
		minus_button->setFontSize(16);
		addChildControl(minus_button);

		SDL_Rect plus_button_client_area{ minus_button_client_area.x + minus_button_client_area.w, client_area_.y, (int)(client_area_.w * 0.1), client_area_.h };
		std::shared_ptr<Action> plus_action = std::make_shared<Action>();
		std::shared_ptr<SDLButton> plus_button = std::make_shared<SDLButton>(parent_,"+", plus_action, plus_button_client_area);
		plus_button->setFontSize(16);
		addChildControl(plus_button);
	}

	void SDLDropDownPlusMinusPane::setItems(std::vector<std::string> items)
	{
	}

	void SDLDropDownPlusMinusPane::respondToAction(Sint32 action)
	{
	}

}
