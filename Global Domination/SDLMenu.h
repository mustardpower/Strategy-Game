#pragma once

#include <string>
#include <vector>

#include "SDL.h"

#include "ColorPreferences.h"
#include "ListItem.h"
#include "SDL_TextRenderer.h"

namespace global_domination
{
	template <class T>
	class SDLMenu : public SDLControl
	{
	public:
		SDLMenu(SDL_Window* parent, int menu_pos_x, int menu_pos_y, int menu_item_height);
		int getSelectedIndex() const;
		void addMenuItem(ListItem<T> menu_item);
		void clearItems();
		bool containsPoint(SDL_Rect aRect, int x, int y);
		bool handleClick(int x, int y);
		void nextMenuItem();
		void previousMenuItem();
		void render(SDL_Renderer* renderer);
		void selectCurrentItem();
		T* selectedItem();
		SDL_Rect textLocationForIndex(const int menu_item_index);
	private:
		int selected_menu_item_index_;
		std::vector<ListItem<T>> menu_items_;
		const int kMenuItemPosX;
		const int kMenuItemPosY;
		const int kMenuItemHeight;
	};

	template <typename T>
	SDLMenu<T>::SDLMenu(SDL_Window* parent, int menu_pos_x, int menu_pos_y, int menu_item_height) : SDLControl(parent),
		kMenuItemPosX(menu_pos_x),
		kMenuItemPosY(menu_pos_y),
		kMenuItemHeight(menu_item_height)
	{
		selected_menu_item_index_ = 0;
	}

	template <typename T>
	int SDLMenu<T>::getSelectedIndex() const
	{
		return selected_menu_item_index_;
	}

	template <typename T>
	void SDLMenu<T>::addMenuItem(ListItem<T> menu_item)
	{
		menu_items_.push_back(menu_item);
	}

	template<class T>
	inline void SDLMenu<T>::clearItems()
	{
		menu_items_.clear();
	}

	template<class T>
	inline bool SDLMenu<T>::containsPoint(SDL_Rect aRect, int x, int y)
	{
		if ((x >= aRect.x) && (x <= (aRect.x + aRect.w)))
		{
			if ((y >= aRect.y) && (y <= (aRect.y + aRect.h)))
			{
				return true;
			}
		}

		return false;
	}

	/* Returns true if click is handled, false if not */
	template<class T>
	inline bool SDLMenu<T>::handleClick(int x, int y)
	{
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

	template <typename T>
	void SDLMenu<T>::nextMenuItem()
	{
		selected_menu_item_index_ = (selected_menu_item_index_ + 1) % menu_items_.size();
	}

	template <typename T>
	void SDLMenu<T>::previousMenuItem()
	{
		selected_menu_item_index_ = (selected_menu_item_index_ - 1) % menu_items_.size();
		if (selected_menu_item_index_ < 0)
		{
			selected_menu_item_index_ = menu_items_.size() - 1;
		}
	}

	template <typename T>
	void SDLMenu<T>::render(SDL_Renderer* renderer)
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
			index++;
		}
	}

	template<class T>
	inline void SDLMenu<T>::selectCurrentItem()
	{
		menu_items_.at(selected_menu_item_index_).invokeAction();
	}

	template<class T>
	inline T* SDLMenu<T>::selectedItem()
	{
		if(!menu_items_.size()) { return nullptr; }
		return menu_items_.at(selected_menu_item_index_).getData();
	}

	template<class T>
	inline SDL_Rect SDLMenu<T>::textLocationForIndex(const int menu_item_index)
	{
		int w = 0;
		int h = 0;

		std::string text = (menu_items_.at(menu_item_index)).reportString();
		text_renderer::getTextDimensions(text, w, h);
		return SDL_Rect{ kMenuItemPosX, kMenuItemPosY + (kMenuItemHeight * menu_item_index), w, h };
	}
}
