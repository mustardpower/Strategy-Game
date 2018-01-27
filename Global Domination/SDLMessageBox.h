#pragma once

#include "SDLListBox.h"

namespace global_domination
{
	template <class T>
	class SDLMessageBox : public SDLListBox<T>
	{
	public:
		SDLMessageBox(SDL_Window* parent, SDL_Rect client_area);
		void drawMessages(SDL_Renderer* renderer);
		bool handleClickOnItems(int x, int y);
		virtual int mapItemIndexToLocationIndex(int item_index);
		void showReadStatus(bool show);
	private:
		bool show_read_status_;
	};

	template<class T>
	inline SDLMessageBox<T>::SDLMessageBox(SDL_Window * parent, SDL_Rect client_area) : SDLListBox<T>(parent, client_area)
	{
		show_read_status_ = false;
	}

	template <class T>
	inline void SDLMessageBox<T>::drawMessages(SDL_Renderer* renderer)
	{
		unsigned int index = 0;
		SDL_Color text_color, background_color;

		for (std::vector<ListItem<T>>::const_reverse_iterator item = items_.crbegin(); item != items_.crend(); item++)
		{
			if (index >= top_visible_index_ && (index < top_visible_index_ + kNumberOfVisibleItems))
			{
				if (index == selected_item_index_)
				{
					text_color = ColorPreferences::getSelectedTextColor();
				}
				else
				{
					text_color = ColorPreferences::getPrimaryTextColor();
				}

				if (item->isUnread() && show_read_status_)
				{
					background_color = SDL_Color{ 30,30,30,0xFF };
				}
				else
				{
					background_color = SDL_Color{ 0,0,0,0xFF };
				}

				SDL_SetRenderDrawColor(renderer, background_color.r, background_color.g, background_color.b, 0xFF);
				SDL_Rect cell_area = SDL_Rect{ client_area_.x, client_area_.y + (kItemHeight * (int)(index - top_visible_index_)), client_area_.w - sliderBarClientArea().w, client_area_.h / kNumberOfVisibleItems };
				SDL_RenderFillRect(renderer, &cell_area);

				SDL_Rect text_location = textLocationForIndex(index);
				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xFF);
				global_domination::text_renderer::renderText(parent_, item->reportString(), text_location, text_color, 15);
			}
			index++;
		}
	}

	template<class T>
	inline bool SDLMessageBox<T>::handleClickOnItems(int x, int y)
	{
		for (unsigned int i = 0; i < items_.size(); i++)
		{
			if (containsPoint(textLocationForIndex(i), x, y))
			{
				selected_item_index_ = i;
				const int location_index = mapItemIndexToLocationIndex(selected_item_index_);
				items_.at(location_index).markAsRead();
				items_.at(location_index).invokeAction();
				return true;
			}
		}

		return false;
	}

	template<class T>
	inline int SDLMessageBox<T>::mapItemIndexToLocationIndex(int item_index)
	{
		return items_.size() - item_index - 1;
	}

	template<class T>
	inline void SDLMessageBox<T>::showReadStatus(bool show)
	{
		show_read_status_ = show;
	}
}