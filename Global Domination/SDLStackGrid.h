#pragma once

#include "StackGridItem.h"

#include <array>

namespace global_domination
{
	template <class T, int X, int Y>
	class SDLStackGrid : public SDLControl
	{
	public:
		SDLStackGrid(SDL_Window* parent, SDL_Rect client_area);
		~SDLStackGrid();
		void addItem(StackGridItem<T> item, int location_x, int location_y);
		void addItemAtNextFreeSlot(StackGridItem<T> item);
		bool containsPoint(SDL_Rect aRect, int x, int y);
		bool handleClick(int x, int y);
		void render(SDL_Renderer* renderer);
		T* selectedItem();
	private:
		SDL_Rect client_area_;
		std::array<std::array<StackGridItem<T>, Y>, X> items_;
		int selected_item_index_x_;
		int selected_item_index_y_;

	};

	template <class T, int X, int Y>
	inline SDLStackGrid<T, X, Y>::SDLStackGrid(SDL_Window * parent, SDL_Rect client_area) : SDLControl(parent)
	{
		client_area_ = client_area;
		selected_item_index_x_ = 0;
		selected_item_index_y_ = 0;
	}

	template<class T, int X, int Y>
	inline SDLStackGrid<T, X, Y>::~SDLStackGrid()
	{
	}

	template <class T, int X, int Y>
	inline void SDLStackGrid<T, X, Y>::addItem(StackGridItem<T> item, int location_x, int location_y)
	{
		items_[location_x][location_y] = item;
	}

	template<class T, int X, int Y>
	inline void SDLStackGrid<T, X, Y>::addItemAtNextFreeSlot(StackGridItem<T> item)
	{
		for (int j = 0; j < Y; j++)
		{
			for (int i = 0; i < X; i++)
			{
				if (items_[i][j].reportString().empty())
				{
					items_[i][j] = item;
					return;
				}
			}
		}
	}

	template <class T, int X, int Y>
	inline bool SDLStackGrid<T, X, Y>::containsPoint(SDL_Rect aRect, int x, int y)
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

	template <class T, int X, int Y>
	inline bool SDLStackGrid<T, X, Y>::handleClick(int x, int y)
	{
		if (!containsPoint(client_area_, x, y))
		{
			return false;
		}

		const int width_per_item = client_area_.w / X;
		const int height_per_item = client_area_.h / Y;
		for (int i = 0; i < items_.size(); i++)
		{
			for (int j = 0; j < items_[i].size(); j++)
			{
				SDL_Rect text_location = SDL_Rect{ client_area_.x + (i * width_per_item), client_area_.y + (j * height_per_item), width_per_item, height_per_item };
				if (containsPoint(text_location, x, y))
				{
					selected_item_index_x_ = i;
					selected_item_index_y_ = j;
					items_[i][j].invokeAction();
					return true;
				}
			}
		}

		return false;
	}

	template <class T, int X, int Y>
	inline void SDLStackGrid<T, X, Y>::render(SDL_Renderer * renderer)
	{
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xFF);
		SDL_RenderFillRect(renderer, &client_area_);

		for (int i = 0; i < items_.size(); i++)
		{
			for (int j = 0; j < items_[i].size(); j++)
			{
				StackGridItem<TradeResource> item = items_[i][j];
				int w = 0;
				int h = 0;
				text_renderer::getTextDimensions(item.reportString(), w, h);
				const int width_per_item = client_area_.w / items_.size();
				const int height_per_item = client_area_.h / items_[i].size();
				SDL_Color text_color = ColorPreferences::getPrimaryTextColor();
				if ((selected_item_index_x_ == i) && (selected_item_index_y_ == j))
				{
					text_color = ColorPreferences::getSelectedTextColor();
				}

				SDL_Rect text_location = SDL_Rect{ client_area_.x + (i * width_per_item) + (int)(0.5 * width_per_item), client_area_.y + (j * height_per_item) + (int)(0.5 * height_per_item), w, h };
				global_domination::text_renderer::renderText(parent_, item.reportString(), text_location, text_color, SDL_Color{ 0,0,0,0xFF }, 15);
			}
		}
	}
	template<class T, int X, int Y>
	inline T * SDLStackGrid<T, X, Y>::selectedItem()
	{
		int a = selected_item_index_x_;
		return (items_[selected_item_index_x_][selected_item_index_y_]).getData();
	}
}
