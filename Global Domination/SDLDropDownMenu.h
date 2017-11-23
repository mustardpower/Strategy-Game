#pragma once

#include "SDLMenu.h"

namespace global_domination
{
	template <class T>
	class SDLDropDownMenu : public SDLMenu<T>
	{
	public:
		SDLDropDownMenu(SDL_Window* parent, int menu_pos_x, int menu_pos_y, int menu_item_height);
		bool handleClick(int x, int y);
		void render(SDL_Renderer* renderer);
		void toggleExpanded();

	private:
		bool is_expanded_;
	};

	template<class T>
	inline SDLDropDownMenu<T>::SDLDropDownMenu(SDL_Window * parent, int menu_pos_x, int menu_pos_y, int menu_item_height): SDLMenu<T>(parent, menu_pos_x, menu_pos_y, menu_item_height)
	{
		is_expanded_ = false;
	}

	template<class T>
	inline bool SDLDropDownMenu<T>::handleClick(int x, int y)
	{
		SDL_Rect text_location = textLocationForIndex(0);
		if (containsPoint(text_location, x, y))
		{
			toggleExpanded();
			return true;
		}

		for (unsigned int i = 1; i < menu_items_.size(); i++)
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

		for (std::vector<ListItem<T>>::const_iterator item = menu_items_.cbegin(); item != menu_items_.cend(); item++)
		{
			if (index == selected_menu_item_index_)
			{
				text_color = ColorPreferences::getSelectedTextColor();
			}
			else
			{
				text_color = ColorPreferences::getPrimaryTextColor();
			}

			SDL_Rect text_location = textLocationForIndex(index);
			global_domination::text_renderer::renderText(parent_, item->reportString(), text_location, text_color, ColorPreferences::getPrimaryBackgroundColor(), 30);

			if (!is_expanded_) { break; }
			index++;
		}
	}

	template<class T>
	inline void SDLDropDownMenu<T>::toggleExpanded()
	{
		is_expanded_ = !is_expanded_;
	}

}