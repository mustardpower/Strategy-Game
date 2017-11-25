#pragma once

#include "SDLMenu.h"

namespace global_domination
{
	template <class T>
	class SDLDropDownMenu : public SDLMenu<T>
	{
	public:
		SDLDropDownMenu(SDL_Window* parent, int top_level_button_pos_x, int top_level_button_pos_y, int sub_menu_pos_x, int sub_menu_pos_y, int menu_item_height);
		void addMenuItem(ListItem<T> menu_item);
		bool handleClick(int x, int y);
		void render(SDL_Renderer* renderer);
		void toggleExpanded();


	private:
		const int kTopLevelButtonPosX;
		const int kTopLevelButtonPosY;
		std::unique_ptr<SDLButton> top_level_button;
		bool is_expanded_;
	};

	template<class T>
	inline SDLDropDownMenu<T>::SDLDropDownMenu(SDL_Window* parent, int top_level_button_pos_x, int top_level_button_pos_y, int sub_menu_pos_x, int sub_menu_pos_y, int menu_item_height): 
		SDLMenu<T>(parent, sub_menu_pos_x, sub_menu_pos_y, menu_item_height), kTopLevelButtonPosX(top_level_button_pos_x), kTopLevelButtonPosY(top_level_button_pos_y)
	{
		is_expanded_ = false;
	}

	template<class T>
	inline void SDLDropDownMenu<T>::addMenuItem(ListItem<T> menu_item)
	{
		if (top_level_button == nullptr)
		{
			top_level_button = std::make_unique<SDLButton>(parent_, menu_item.reportString(), menu_item.getAction(), kTopLevelButtonPosX, kTopLevelButtonPosY, 150, kMenuItemHeight);
			top_level_button->useSecondaryColorScheme();
		}
		else
		{
			menu_items_.push_back(menu_item);
		}
		
	}

	template<class T>
	inline bool SDLDropDownMenu<T>::handleClick(int x, int y)
	{
		if (top_level_button->containsPoint(x, y))
		{
			toggleExpanded();
			return true;
		}

		for (unsigned int i = 0; i < menu_items_.size(); i++)
		{
			SDL_Rect text_location = textLocationForIndex(i);
			// should already have cached text locations by this point??

			if (containsPoint(text_location, x, y))
			{
				selected_menu_item_index_ = i;
				menu_items_.at(i).invokeAction();
				return true;
			}
		}

		return false;
	}

	template<class T>
	inline void SDLDropDownMenu<T>::render(SDL_Renderer* renderer)
	{
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xFF);

		int index = 0;
		SDL_Color text_color;

		top_level_button->render(renderer);

		if (is_expanded_)
		{
			for (std::vector<ListItem<T>>::const_iterator item = menu_items_.cbegin(); item != menu_items_.cend(); item++)
			{
				SDL_Rect menu_client_area{ kMenuItemPosX, kMenuItemPosY, 150, kMenuItemHeight * menu_items_.size() };
				
				SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0xFF);
				SDL_RenderFillRect(renderer, &menu_client_area);

				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xFF);
				SDL_RenderDrawRect(renderer, &menu_client_area);

				text_color = getMenuItemTextColor(index);
				SDL_Rect text_location = textLocationForIndex(index);
				global_domination::text_renderer::renderText(parent_, item->reportString(), text_location, text_color, ColorPreferences::getPrimaryBackgroundColor(), 30);
			}
		}
	}

	template<class T>
	inline void SDLDropDownMenu<T>::toggleExpanded()
	{
		is_expanded_ = !is_expanded_;
	}

}