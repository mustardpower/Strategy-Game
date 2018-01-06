#pragma once

#include "SDL.h"

#include <functional>

#include "ColorPreferences.h"
#include "SDL_TextRenderer.h"
#include "DataGridCell.h"

namespace global_domination
{
	template <class T, int C, int R>
	class SDLDataGrid : public SDLControl
	{
	public:
		SDLDataGrid(SDL_Window* parent, SDL_Rect client_area);
		~SDLDataGrid();
		void addItem(std::shared_ptr<DataGridCell<T>> item, int location_x, int location_y);
		bool containsPoint(SDL_Rect aRect, int x, int y);
		bool handleClick(int x, int y);
		void render(SDL_Renderer * renderer);
		void setSelector(int column_y, std::function<std::string(const T&)> selector);
	private:
		SDL_Rect client_area_;
		std::array<std::array<std::shared_ptr<DataGridCell<T>>, R>, C> items_;
		std::array<std::function<std::string(const T&)>, C> selectors_;
	};

	template <class T, int C, int R>
	inline SDLDataGrid<T, C, R>::SDLDataGrid(SDL_Window * parent, SDL_Rect client_area) : SDLControl(parent, client_area)
	{
		client_area_ = client_area;
	}

	template <class T, int C, int R>
	inline SDLDataGrid<T, C, R>::~SDLDataGrid()
	{
	}

	template <class T, int C, int R>
	inline void SDLDataGrid<T, C, R>::addItem(std::shared_ptr<DataGridCell<T>> item, int location_x, int location_y)
	{
		items_[location_x][location_y] = item;
	}

	template <class T, int C, int R>
	inline bool SDLDataGrid<T, C, R>::containsPoint(SDL_Rect aRect, int x, int y)
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

	template <class T, int C, int R>
	inline bool SDLDataGrid<T, C, R>::handleClick(int x, int y)
	{
		if (!containsPoint(client_area_, x, y))
		{
			return false;
		}

		const int width_per_item = client_area_.w / C;
		const int height_per_item = client_area_.h / R;
		for (int i = 0; i < items_.size(); i++)
		{
			for (int j = 0; j < items_[i].size(); j++)
			{
				SDL_Rect text_location = SDL_Rect{ client_area_.x + (i * width_per_item), client_area_.y + (j * height_per_item), width_per_item, height_per_item };
				if (containsPoint(text_location, x, y))
				{
					items_[i][j]->invokeAction();
					return true;
				}
			}
		}

		return false;
	}

	template <class T, int C, int R>
	inline void SDLDataGrid<T, C, R>::render(SDL_Renderer * renderer)
	{
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xFF);
		SDL_RenderFillRect(renderer, &client_area_);

		for (int column = 0; column < items_.size(); column++)
		{
			for (int row = 0; row < items_[column].size(); row++)
			{
				std::shared_ptr<DataGridCell<T>> item = items_[column][row];
				std::function<std::string(const T&)> selector = selectors_[column];
				if (selector)
				{
					int w = 0;
					int h = 0;
					const T* data = item->getData();
					std::string text = selector(*data);
					text_renderer::getTextDimensions(text, w, h);
					const int width_per_item = client_area_.w / items_.size();
					const int height_per_item = client_area_.h / items_[column].size();
					SDL_Color text_color = ColorPreferences::getPrimaryTextColor();
					SDL_Rect text_location = SDL_Rect{ client_area_.x + (column * width_per_item) + (int)(0.5 * width_per_item), client_area_.y + (row * height_per_item) + (int)(0.5 * height_per_item), w, h };
					global_domination::text_renderer::renderText(parent_, text, text_location, text_color, SDL_Color{ 0,0,0,0xFF }, 15);
				}

			}
		}
	}

	template <class T, int C, int R>
	inline void SDLDataGrid<T, C, R>::setSelector(int column_index, std::function<std::string(const T&)> selector)
	{
		selectors_[column_index] = selector;
	}
}
