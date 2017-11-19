#pragma once

#include <string>
#include <vector>

#include "SDL.h"
#include "SDL2_gfxPrimitives.h"
#include "SDL_TextRenderer.h"

#include "ListItem.h"

namespace global_domination
{
	template <class T>
	class SDLListBox : public SDLControl
	{
	public:
		SDLListBox(SDL_Window* parent, SDL_Rect client_area, int item_height);
		int getSelectedIndex() const;
		void addItem(ListItem<T> menu_item);
		void clearItems();
		bool containsPoint(SDL_Rect aRect, int x, int y);
		void drawSliderBar(SDL_Renderer* renderer);
		bool handleClick(int x, int y);
		void nextItem();
		void previousItem();
		void render(SDL_Renderer* renderer);
		void selectCurrentItem();
		T* selectedItem();
		SDL_Rect textLocationForIndex(const int item_index);
	private:
		SDL_Rect client_area_;
		int selected_item_index_;
		SDL_Window* parent_window_;
		std::vector<ListItem<T>> items_;
		const int kItemHeight;
	};

	template <typename T>
	SDLListBox<T>::SDLListBox(SDL_Window*  parent, SDL_Rect client_area, int item_height) :
		kItemHeight(item_height)
	{
		client_area_ = client_area;
		selected_item_index_ = 0;
		parent_window_ = parent;
	}

	template <typename T>
	int SDLListBox<T>::getSelectedIndex() const
	{
		return selected_item_index_;
	}

	template <typename T>
	void SDLListBox<T>::addItem(ListItem<T> item)
	{
		items_.push_back(item);
	}

	template<class T>
	inline void SDLListBox<T>::clearItems()
	{
		items_.clear();
	}

	template<class T>
	inline bool SDLListBox<T>::containsPoint(SDL_Rect aRect, int x, int y)
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
	inline void SDLListBox<T>::drawSliderBar(SDL_Renderer* renderer)
	{
		SDL_SetRenderDrawColor(renderer, 134, 136, 140, 0xFF);
		SDL_RenderFillRect(renderer, &client_area_);

		SDL_Rect slider_bar_client_area{ client_area_.x + (client_area_.w * 0.90), client_area_.y, client_area_.w * 0.1, client_area_.h };
		SDL_SetRenderDrawColor(renderer, 255, 136, 140, 0xFF);
		SDL_RenderFillRect(renderer, &slider_bar_client_area);

		SDL_Rect up_arrow_client_area{ slider_bar_client_area.x, slider_bar_client_area.y, slider_bar_client_area.w, slider_bar_client_area.h * 0.06 };
		SDL_SetRenderDrawColor(renderer, 134, 255, 140, 0xFF);
		SDL_RenderFillRect(renderer, &up_arrow_client_area);

		filledTrigonRGBA(renderer,
			up_arrow_client_area.x, up_arrow_client_area.y + up_arrow_client_area.h,
			up_arrow_client_area.x + (up_arrow_client_area.w / 2), up_arrow_client_area.y,
			up_arrow_client_area.x + up_arrow_client_area.w, up_arrow_client_area.y + up_arrow_client_area.h,
			0, 0, 255, 255);

		SDL_Rect down_arrow_client_area{ slider_bar_client_area.x, slider_bar_client_area.y + (slider_bar_client_area.h * 0.94), slider_bar_client_area.w, slider_bar_client_area.h * 0.06 };
		SDL_SetRenderDrawColor(renderer, 134, 255, 140, 0xFF);
		SDL_RenderFillRect(renderer, &down_arrow_client_area);

		filledTrigonRGBA(renderer,
			down_arrow_client_area.x, down_arrow_client_area.y,
			down_arrow_client_area.x + (down_arrow_client_area.w / 2), down_arrow_client_area.y + down_arrow_client_area.h,
			down_arrow_client_area.x + down_arrow_client_area.w, down_arrow_client_area.y,
			0, 0, 255, 255);
	}

	/* Returns true if click is handled, false if not */
	template<class T>
	inline bool SDLListBox<T>::handleClick(int x, int y)
	{
		for (unsigned int i = 0; i < items_.size(); i++)
		{
			SDL_Rect text_location = textLocationForIndex(i);
			// should already have cached text locations by this point??

			if (containsPoint(text_location, x, y))
			{
				selected_item_index_ = i;
				items_.at(i).invokeAction();
				return true;
			}
		}

		return false;
	}

	template <typename T>
	void SDLListBox<T>::nextItem()
	{
		selected_item_index_ = (selected_item_index_ + 1) % menu_items_.size();
	}

	template <typename T>
	void SDLListBox<T>::previousItem()
	{
		selected_menu_item_index_ = (selected_menu_item_index_ - 1) % menu_items_.size();
		if (selected_menu_item_index_ < 0)
		{
			selected_menu_item_index_ = menu_items_.size() - 1;
		}
	}

	template <typename T>
	void SDLListBox<T>::render(SDL_Renderer* renderer)
	{
		int index = 0;
		SDL_Color text_color;

		drawSliderBar(renderer);

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xFF);

		for (std::vector<ListItem<T>>::const_iterator item = items_.cbegin(); item != items_.cend(); item++)
		{
			if (index == selected_item_index_)
			{
				text_color = { 0,255,0 };
			}
			else
			{
				text_color = { 255,0,0 };
			}

			SDL_Rect text_location = textLocationForIndex(index);
			global_domination::text_renderer::renderText(parent_window_, item->reportString(), text_location, text_color);
			index++;
		}
	}

	template<class T>
	inline void SDLListBox<T>::selectCurrentItem()
	{
		menu_items_.at(selected_menu_item_index_).invokeAction();
	}

	template<class T>
	inline T* SDLListBox<T>::selectedItem()
	{
		if (!items_.size()) { return nullptr; }
		return items_.at(selected_item_index_).getData();
	}

	template<class T>
	inline SDL_Rect SDLListBox<T>::textLocationForIndex(const int menu_item_index)
	{
		int w = 0;
		int h = 0;

		std::string text = (items_.at(menu_item_index)).reportString();
		text_renderer::getTextDimensions(text, w, h);
		
		return SDL_Rect{ client_area_.x, client_area_.y + (kItemHeight * menu_item_index), w, h };
	}
}
