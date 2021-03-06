#pragma once

#include <string>
#include <vector>

#include "SDL.h"
#include "SDL2_gfxPrimitives.h"

#include "ColorPreferences.h"
#include "ListItem.h"
#include "SDL_TextRenderer.h"

namespace global_domination
{
	template <class T>
	class SDLListBox : public SDLControl
	{
	public:
		SDLListBox(SDL_Window* parent, SDL_Rect client_area);
		int getSelectedIndex() const;
		void addItem(ListItem<T> menu_item);
		void clearItems();
		virtual void drawMessages(SDL_Renderer* renderer);
		void drawSliderBar(SDL_Renderer* renderer);
		void drawSliderBarUpArrow(SDL_Renderer* renderer);
		void drawSliderBarDownArrow(SDL_Renderer* renderer);
		bool handleClick(int x, int y);
		virtual bool handleClickOnItems(int x, int y);
		bool isEmpty();
		virtual int mapItemIndexToLocationIndex(int item_index);
		void nextItem();
		void previousItem();
		void render(SDL_Renderer* renderer);
		void selectCurrentItem();
		T* selectedItem();
		SDL_Rect sliderBarClientArea();
		SDL_Rect sliderBarDownArrowClientArea();
		SDL_Rect sliderBarUpArrowClientArea();
		SDL_Rect textLocationForIndex(const unsigned int item_index);
	protected:

		SDL_Rect client_area_;
		std::vector<ListItem<T>> items_;
		unsigned int selected_item_index_;
		unsigned int top_visible_index_;

		const int kItemHeight;
		// Number of visible items depends on the font size 
		//so I'm not sure how to dynamically calculate this value
		const int kNumberOfVisibleItems = 10;

	private:
		
	};

	template <typename T>
	SDLListBox<T>::SDLListBox(SDL_Window*  parent, SDL_Rect client_area) : SDLControl(parent, client_area),
		kItemHeight((int)(client_area.h * 0.1))
	{
		client_area_ = client_area;
		selected_item_index_ = 0;
		top_visible_index_ = 0;
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

	template <class T>
	inline void SDLListBox<T>::drawMessages(SDL_Renderer* renderer)
	{
		unsigned int index = 0;
		SDL_Color text_color;

		for (std::vector<ListItem<T>>::const_iterator item = items_.cbegin(); item != items_.cend(); item++)
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

				SDL_Rect text_location = textLocationForIndex(index);
				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xFF);
				global_domination::text_renderer::renderText(parent_, item->reportString(), text_location, text_color, 15);
			}
			index++;
		}
	}

	template<class T>
	inline void SDLListBox<T>::drawSliderBar(SDL_Renderer* renderer)
	{
		SDL_Color slider_arrow_color = ColorPreferences::getPrimaryBackgroundColor();
		SDL_SetRenderDrawColor(renderer, slider_arrow_color.r, slider_arrow_color.g, slider_arrow_color.b, 0xFF);
		SDL_RenderFillRect(renderer, &sliderBarClientArea());

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xFF);
		SDL_RenderDrawRect(renderer, &sliderBarClientArea());

		drawSliderBarUpArrow(renderer);
		drawSliderBarDownArrow(renderer);
	}

	template<class T>
	inline void SDLListBox<T>::drawSliderBarUpArrow(SDL_Renderer * renderer)
	{
		SDL_Rect up_arrow_client_area = sliderBarUpArrowClientArea();
		SDL_Color slider_arrow_color = ColorPreferences::getPrimaryBackgroundColor();
		SDL_SetRenderDrawColor(renderer, slider_arrow_color.r, slider_arrow_color.g, slider_arrow_color.b, 0xFF);
		SDL_RenderFillRect(renderer, &up_arrow_client_area);

		SDL_SetRenderDrawColor(renderer, 0,0,0, 0xFF);
		SDL_RenderDrawRect(renderer, &up_arrow_client_area);

		filledTrigonRGBA(renderer,
			up_arrow_client_area.x + (int)(up_arrow_client_area.w * 0.05), up_arrow_client_area.y + up_arrow_client_area.h,
			up_arrow_client_area.x + (int)(up_arrow_client_area.w / 2), up_arrow_client_area.y,
			up_arrow_client_area.x + (int)(up_arrow_client_area.w * 0.95), up_arrow_client_area.y + up_arrow_client_area.h,
			0, 0, 0, 255);
	}

	template<class T>
	inline void SDLListBox<T>::drawSliderBarDownArrow(SDL_Renderer * renderer)
	{
		SDL_Rect down_arrow_client_area = sliderBarDownArrowClientArea();
		SDL_Color slider_arrow_color = ColorPreferences::getPrimaryBackgroundColor();
		SDL_SetRenderDrawColor(renderer, slider_arrow_color.r, slider_arrow_color.g, slider_arrow_color.b, 0xFF);
		SDL_RenderFillRect(renderer, &down_arrow_client_area);

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xFF);
		SDL_RenderDrawRect(renderer, &down_arrow_client_area);

		filledTrigonRGBA(renderer,
			down_arrow_client_area.x + (int)(down_arrow_client_area.w * 0.05), down_arrow_client_area.y,
			down_arrow_client_area.x + (int)(down_arrow_client_area.w / 2), down_arrow_client_area.y + down_arrow_client_area.h,
			down_arrow_client_area.x + (int)(down_arrow_client_area.w * 0.95), down_arrow_client_area.y,
			0, 0, 0, 255);
	}

	/* Returns true if click is handled, false if not */
	template<class T>
	inline bool SDLListBox<T>::handleClick(int x, int y)
	{
		if (!is_visible_)
		{
			return false;
		}

		if (!containsPoint(client_area_, x, y))
		{
			return false;
		}

		if (handleClickOnItems(x, y)) { return true; }

		if (containsPoint(sliderBarUpArrowClientArea(), x, y))
		{
			if (top_visible_index_ > 0)
			{
				top_visible_index_--;
			}
			return true;
		}

		if (containsPoint(sliderBarDownArrowClientArea(), x, y))
		{
			if (!items_.empty() && (top_visible_index_ < items_.size() - 1))
			{
				top_visible_index_++;
				return true;
			}
		}

		return false;
	}

	template<class T>
	inline bool SDLListBox<T>::handleClickOnItems(int x, int y)
	{
		for (unsigned int i = 0; i < items_.size(); i++)
		{
			if (containsPoint(textLocationForIndex(i), x, y))
			{
				selected_item_index_ = i;
				items_.at(i).markAsRead();
				items_.at(i).invokeAction();
				return true;
			}
		}

		return false;
	}

	template<class T>
	inline bool SDLListBox<T>::isEmpty()
	{
		return items_.empty();
	}

	template<class T>
	inline int SDLListBox<T>::mapItemIndexToLocationIndex(int item_index)
	{
		return item_index;
	}

	template <typename T>
	void SDLListBox<T>::nextItem()
	{
		selected_item_index_ = (selected_item_index_ + 1) % items_.size();
	}

	template <typename T>
	void SDLListBox<T>::previousItem()
	{
		selected_item_index_ = (selected_item_index_ - 1) % items_.size();
		if (selected_item_index_ < 0)
		{
			selected_item_index_ = items_.size() - 1;
		}
	}

	template <typename T>
	void SDLListBox<T>::render(SDL_Renderer* renderer)
	{
		if (is_visible_)
		{
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xFF);
			SDL_RenderFillRect(renderer, &client_area_);

			drawSliderBar(renderer);
			drawMessages(renderer);
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
		if (items_.size() <= selected_item_index_) { selected_item_index_ = 0; }
		const int location_index = mapItemIndexToLocationIndex(selected_item_index_);
		items_.at(location_index).markAsRead();
		return items_.at(location_index).getData();
	}

	template<class T>
	inline SDL_Rect SDLListBox<T>::sliderBarClientArea()
	{
		int list_width = (int)(client_area_.w * 0.9);
		int slider_bar_width = (int)(client_area_.w * 0.1);
		return SDL_Rect { client_area_.x + list_width, client_area_.y, slider_bar_width, client_area_.h };
	}

	template<class T>
	inline SDL_Rect SDLListBox<T>::sliderBarDownArrowClientArea()
	{
		int arrow_height = (int)(sliderBarClientArea().h * 0.06);
		return SDL_Rect { sliderBarClientArea().x, sliderBarClientArea().y + sliderBarClientArea().h - arrow_height, sliderBarClientArea().w, arrow_height };
	}

	template<class T>
	inline SDL_Rect SDLListBox<T>::sliderBarUpArrowClientArea()
	{
		int arrow_height = (int)(sliderBarClientArea().h * 0.06);
		return SDL_Rect { sliderBarClientArea().x, sliderBarClientArea().y, sliderBarClientArea().w, arrow_height };
	}

	template<class T>
	inline SDL_Rect SDLListBox<T>::textLocationForIndex(const unsigned int menu_item_index)
	{
		ListItem<T> list_item = items_.at(menu_item_index);
		std::shared_ptr<SDL_Rect> cached_text_location = list_item.getTextLocation();
		if (cached_text_location) { return *cached_text_location; }

		int w = 0;
		int h = 0;
		text_renderer::getTextDimensions(list_item.reportString(), w, h);
		const int location_index = menu_item_index - top_visible_index_;
		SDL_Rect text_location = SDL_Rect{ client_area_.x, client_area_.y + (kItemHeight * location_index), w, h };
		list_item.setTextLocation(text_location);
		return text_location;
	}
}
