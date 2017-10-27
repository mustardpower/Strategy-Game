#pragma once

#include <string>
#include <vector>

#include "SDL.h"
#include "SDL_ttf.h"

#include "MenuItem.h"

namespace global_domination
{
	template <class T>
	class SDLMenu
	{
	private:
		int selected_menu_item_index_;
		SDL_Window* parent_window_;
		std::vector<MenuItem<T>> menu_items_;
		const int kMenuItemPosX;
		const int kMenuItemPosY;
		const int kMenuItemHeight;
	public:
		SDLMenu(SDL_Window* parent, SDL_Rect client_area);
		int getSelectedIndex() const;
		void addMenuItem(MenuItem<T> menu_item);
		bool containsPoint(SDL_Rect aRect, int x, int y);
		void handleClick(int x, int y);
		void nextMenuItem();
		void previousMenuItem();
		void renderMenu(SDL_Renderer* renderer);
		void selectCurrentItem();
		T selectedItem();
		SDL_Rect textLocationForIndex(TTF_Font* font, const int menu_item_index);
	};

	template <typename T>
	SDLMenu<T>::SDLMenu(SDL_Window*  parent, SDL_Rect client_area) :
		kMenuItemPosX(client_area.w * 0.2),
		kMenuItemPosY(client_area.h * 0.3),
		kMenuItemHeight(client_area.h * 0.1)
	{
		selected_menu_item_index_ = 0;
		parent_window_ = parent;
	}

	template <typename T>
	int SDLMenu<T>::getSelectedIndex() const
	{
		return selected_menu_item_index_;
	}

	template <typename T>
	void SDLMenu<T>::addMenuItem(MenuItem<T> menu_item)
	{
		menu_items_.push_back(menu_item);
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

	template<class T>
	inline void SDLMenu<T>::handleClick(int x, int y)
	{
		for (unsigned int i = 0; i < menu_items_.size(); i++)
		{
			SDL_Rect text_location = textLocationForIndex(text_renderer::getFont(), i);
			// should already have cached text locations by this point??

			if (containsPoint(text_location, x, y))
			{
				selected_menu_item_index_ = i;
				menu_items_.at(i).invokeAction();
			}
		}
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
	void SDLMenu<T>::renderMenu(SDL_Renderer* renderer)
	{
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xFF);
		SDL_RenderClear(renderer);

		int index = 0;
		SDL_Color text_color;

		TTF_Font* font = text_renderer::getFont();
		if (!font) { return; }


		for (std::vector<MenuItem<T>>::const_iterator item = menu_items_.cbegin(); item != menu_items_.cend(); item++)
		{
			if (index == selected_menu_item_index_)
			{
				text_color = { 0,255,0 };
			}
			else
			{
				text_color = { 255,0,0 };
			}

			text_renderer::renderText(parent_window_, item->reportString(), textLocationForIndex(font, index), text_color);
			index++;
		}

		SDL_UpdateWindowSurface(parent_window_);
	}

	template<class T>
	inline void SDLMenu<T>::selectCurrentItem()
	{
		menu_items_.at(selected_menu_item_index_).invokeAction();
	}

	template<class T>
	inline T SDLMenu<T>::selectedItem()
	{
		return menu_items_.at(selected_menu_item_index_).getData();
	}

	template<class T>
	inline SDL_Rect SDLMenu<T>::textLocationForIndex(TTF_Font* font, const int menu_item_index)
	{
		int w = 0;
		int h = 0;

		std::string text = (menu_items_.at(menu_item_index)).reportString();
		TTF_SizeText(font, text.c_str(), &w, &h);
		return SDL_Rect{ kMenuItemPosX, kMenuItemPosY + (kMenuItemHeight * menu_item_index), w, h };
	}
}
