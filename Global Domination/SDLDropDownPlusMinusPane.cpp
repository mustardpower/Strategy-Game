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
		SDL_Rect dropdown_client_area{ client_area_.x, client_area_.y, (int)(client_area_.w * 0.8), client_area_.h };
		dropdown_list_ = std::make_shared<SDLDropDownList>(parent_, dropdown_client_area);
		dropdown_list_->setFontSize(16);
		addChildControl(dropdown_list_);

		SDL_Rect minus_button_client_area{ client_area_.x + dropdown_client_area.w, client_area_.y, (int)(client_area_.w * 0.1), client_area_.h };
		std::shared_ptr<Action> minus_action = std::make_shared<Action>(TYPES::ACTION_LIST::DECREASE_LISTBOX_VALUE);
		std::shared_ptr<SDLButton> minus_button = std::make_shared<SDLButton>(parent_,"-", minus_action, minus_button_client_area);
		minus_button->setFontSize(16);
		addChildControl(minus_button);

		SDL_Rect plus_button_client_area{ minus_button_client_area.x + minus_button_client_area.w, client_area_.y, (int)(client_area_.w * 0.1), client_area_.h };
		std::shared_ptr<Action> plus_action = std::make_shared<Action>(TYPES::ACTION_LIST::INCREASE_LISTBOX_VALUE);
		std::shared_ptr<SDLButton> plus_button = std::make_shared<SDLButton>(parent_,"+", plus_action, plus_button_client_area);
		plus_button->setFontSize(16);
		addChildControl(plus_button);
	}

	void SDLDropDownPlusMinusPane::setItems(std::vector<std::string> items)
	{
		dropdown_list_->setItems(items);
	}

	void SDLDropDownPlusMinusPane::respondToAction(Sint32 action)
	{
		const double kIncrement = 0.25;
		switch (action)
		{
			case TYPES::ACTION_LIST::DECREASE_LISTBOX_VALUE:
			{
				size_t size;
				std::string value = dropdown_list_->getText();
				if (!value.empty())
				{
					double current_number = std::stod(value, &size);
					double new_number = current_number -= kIncrement;
					if (new_number >= 0.0)
					{
						dropdown_list_->setText(std::to_string(new_number) + "%");
					}
				}
			}
			break;
			case TYPES::ACTION_LIST::INCREASE_LISTBOX_VALUE:
			{
				size_t size;
				std::string value = dropdown_list_->getText();
				if (!value.empty())
				{
					double current_number = std::stod(value, &size);
					double new_number = current_number += kIncrement;
					if (new_number < 100.25)
					{
						dropdown_list_->setText(std::to_string(new_number) + "%");
					}
				}
			}
			break;
		default:
			break;
		}
	}

}
