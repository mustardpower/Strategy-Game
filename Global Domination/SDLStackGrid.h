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
		void addItem(StackGridItem<T> item, int location_x, int location_y);
		bool containsPoint(SDL_Rect aRect, int x, int y);
		bool handleClick(int x, int y);
		void render(SDL_Renderer* renderer);
	private:
		SDL_Rect client_area_;
		std::array<std::array<StackGridItem<T>, Y>, X> items;
	};

	template <class T, int X, int Y>
	inline SDLStackGrid<T, X, Y>::SDLStackGrid(SDL_Window * parent, SDL_Rect client_area) : SDLControl(parent)
	{
		client_area_ = client_area;
	}

	template <class T, int X, int Y>
	inline void SDLStackGrid<T, X, Y>::addItem(StackGridItem<T> item, int location_x, int location_y)
	{
		items[location_x][location_y] = item;
	}

	template <class T, int X, int Y>
	inline bool SDLStackGrid<T, X, Y>::containsPoint(SDL_Rect aRect, int x, int y)
	{
		return false;
	}

	template <class T, int X, int Y>
	inline bool SDLStackGrid<T, X, Y>::handleClick(int x, int y)
	{
		return false;
	}

	template <class T, int X, int Y>
	inline void SDLStackGrid<T, X, Y>::render(SDL_Renderer * renderer)
	{
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xFF);
		SDL_RenderFillRect(renderer, &client_area_);

		for (int i = 0; i < items.size(); i++)
		{
			for (int j = 0; j < items[i].size(); j++)
			{
				StackGridItem<TradeResource> item = items[i][j];
				int w = 0;
				int h = 0;
				text_renderer::getTextDimensions(item.reportString(), w, h);
				const int width_per_item = client_area_.w / items.size();
				const int height_per_item = client_area_.h / items[i].size();
				SDL_Rect text_location = SDL_Rect{ client_area_.x + (i * width_per_item) + (int)(0.5 * width_per_item), client_area_.y + (j * height_per_item) + (int)(0.5 * height_per_item), w, h };
				global_domination::text_renderer::renderText(parent_, item.reportString(), text_location, ColorPreferences::getPrimaryTextColor(), SDL_Color{ 0,0,0,0xFF }, 15);
			}
		}
	}
}
