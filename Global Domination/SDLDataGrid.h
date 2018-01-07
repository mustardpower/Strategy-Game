#pragma once

#include "SDL.h"
#include "SDL2_gfxPrimitives.h"

#include <functional>

#include "ColorPreferences.h"
#include "DataGridCell.h"
#include "SDL_TextRenderer.h"

namespace global_domination
{
	template <class T, int C, int R>
	class SDLDataGrid : public SDLControl
	{
	public:
		SDLDataGrid(SDL_Window* parent, SDL_Rect client_area);
		~SDLDataGrid();
		void addItem(std::shared_ptr<DataGridCell<T>> item, int location_x, int location_y);
		int cellHeight();
		int cellWidth();
		bool containsPoint(SDL_Rect aRect, int x, int y);
		void drawSliderBar(SDL_Renderer* renderer);
		void drawSliderBarUpArrow(SDL_Renderer* renderer);
		void drawSliderBarDownArrow(SDL_Renderer* renderer);
		bool handleClick(int x, int y);
		void render(SDL_Renderer * renderer);
		void renderCells(SDL_Renderer * renderer);
		void renderCell(SDL_Renderer* renderer, int column, int row);
		const int sliderArrowHeight();
		const int sliderArrowMargin();
		const int sliderArrowWidth();
		SDL_Rect sliderBarClientArea();
		SDL_Rect sliderBarDownArrowClientArea();
		SDL_Rect sliderBarUpArrowClientArea();
	private:
		SDL_Rect client_area_;
		std::array<std::vector<std::shared_ptr<DataGridCell<T>>>, C> items_;
		int top_visible_index_;
	};

	template <class T, int C, int R>
	inline SDLDataGrid<T, C, R>::SDLDataGrid(SDL_Window * parent, SDL_Rect client_area) : SDLControl(parent, client_area)
	{
		client_area_ = client_area;
		top_visible_index_ = 0;
	}

	template <class T, int C, int R>
	inline SDLDataGrid<T, C, R>::~SDLDataGrid()
	{
	}

	template <class T, int C, int R>
	inline void SDLDataGrid<T, C, R>::addItem(std::shared_ptr<DataGridCell<T>> item, int location_x, int location_y)
	{
		items_[location_x].push_back(item);
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
	inline void SDLDataGrid<T, C, R>::drawSliderBar(SDL_Renderer* renderer)
	{
		SDL_Color slider_arrow_color = ColorPreferences::getPrimaryBackgroundColor();
		SDL_SetRenderDrawColor(renderer, slider_arrow_color.r, slider_arrow_color.g, slider_arrow_color.b, 0xFF);
		SDL_RenderFillRect(renderer, &sliderBarClientArea());

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xFF);
		SDL_RenderDrawRect(renderer, &sliderBarClientArea());

		drawSliderBarUpArrow(renderer);
		drawSliderBarDownArrow(renderer);
	}

	template <class T, int C, int R>
	inline void SDLDataGrid<T, C, R>::drawSliderBarUpArrow(SDL_Renderer * renderer)
	{
		SDL_Rect up_arrow_client_area = sliderBarUpArrowClientArea();
		filledTrigonRGBA(renderer,
			up_arrow_client_area.x + (up_arrow_client_area.w * 0.05), up_arrow_client_area.y + up_arrow_client_area.h,
			up_arrow_client_area.x + (up_arrow_client_area.w / 2), up_arrow_client_area.y,
			up_arrow_client_area.x + (up_arrow_client_area.w * 0.95), up_arrow_client_area.y + up_arrow_client_area.h,
			0, 0, 0, 255);
	}

	template <class T, int C, int R>
	inline void SDLDataGrid<T, C, R>::drawSliderBarDownArrow(SDL_Renderer * renderer)
	{
		SDL_Rect down_arrow_client_area = sliderBarDownArrowClientArea();
		filledTrigonRGBA(renderer,
			down_arrow_client_area.x + (down_arrow_client_area.w * 0.05), down_arrow_client_area.y,
			down_arrow_client_area.x + (down_arrow_client_area.w / 2), down_arrow_client_area.y + down_arrow_client_area.h,
			down_arrow_client_area.x + (down_arrow_client_area.w * 0.95), down_arrow_client_area.y,
			0, 0, 0, 255);
	}

	template <class T, int C, int R>
	inline bool SDLDataGrid<T, C, R>::handleClick(int x, int y)
	{
		SDL_Rect slider_bar_client_area = sliderBarClientArea();
		bool mainClientContainsPoint = containsPoint(client_area_, x, y);
		bool sliderBarContainsPoint = containsPoint(slider_bar_client_area, x, y);
		if (!(mainClientContainsPoint || sliderBarContainsPoint))
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
			// Assumes all columns have the same number of items (i.e same as the first column) 
			if (!items_.empty() && (top_visible_index_ < items_[0].size() - 1))
			{
				top_visible_index_++;
				return true;
			}
		}

		return false;
	}

	template <class T, int C, int R>
	inline void SDLDataGrid<T, C, R>::render(SDL_Renderer * renderer)
	{
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0xFF);
		SDL_RenderFillRect(renderer, &client_area_);

		SDL_SetRenderDrawColor(renderer, 0,0,0, 0xFF);
		SDL_RenderDrawRect(renderer, &client_area_);

		renderCells(renderer);

		drawSliderBar(renderer);
	}

	template<class T, int C, int R>
	inline void SDLDataGrid<T, C, R>::renderCells(SDL_Renderer * renderer)
	{
		for (int column = 0; column < items_.size(); column++)
		{
			SDL_RenderDrawLine(renderer, client_area_.x + (column * cellWidth()), client_area_.y, client_area_.x + (column * cellWidth()), client_area_.y + client_area_.h);

			for (int grid_row = 0; grid_row < R; grid_row++)
			{
				SDL_RenderDrawLine(renderer, client_area_.x, client_area_.y + (grid_row * cellHeight()), client_area_.x + client_area_.w, client_area_.y + (grid_row * cellHeight()));
				const int item_index = grid_row + top_visible_index_;
				if (item_index < items_[column].size())
				{
					std::shared_ptr<DataGridCell<T>> item = items_[column][item_index];
					if (item)
					{
						renderCell(renderer, column, grid_row);
					}
				}
			}
		}
	}

	template<class T, int C, int R>
	inline void SDLDataGrid<T, C, R>::renderCell(SDL_Renderer * renderer, int column, int grid_row)
	{
		int w, h = 0;
		const int item_index = grid_row + top_visible_index_;
		std::string text = items_[column][item_index]->reportString();
		text_renderer::getTextDimensions(text, w, h);
		SDL_Color text_color = ColorPreferences::getPrimaryTextColor();
		SDL_Rect text_location = SDL_Rect{ client_area_.x + (column * cellWidth()) + (int)(0.5 * cellWidth()), client_area_.y + (grid_row * cellHeight()) + (int)(0.5 * cellHeight()), w, h };
		global_domination::text_renderer::renderText(parent_, text, text_location, text_color, SDL_Color{ 0,0,0,0xFF }, 15);
	}

	template<class T, int C, int R>
	inline const int SDLDataGrid<T, C, R>::sliderArrowHeight()
	{
		return sliderArrowWidth();
	}

	template<class T, int C, int R>
	inline const int SDLDataGrid<T, C, R>::sliderArrowMargin()
	{
		return 5;
	}

	template<class T, int C, int R>
	inline const int SDLDataGrid<T, C, R>::sliderArrowWidth()
	{
		return sliderBarClientArea().w - (2 * sliderArrowMargin());
	}

	template<class T, int C, int R>
	inline SDL_Rect SDLDataGrid<T, C, R>::sliderBarClientArea()
	{
		const int kSliderBarWidth = 20;
		return SDL_Rect{ client_area_.x + client_area_.w, client_area_.y, kSliderBarWidth, client_area_.h };
	}

	template<class T, int C, int R>
	inline SDL_Rect SDLDataGrid<T, C, R>::sliderBarDownArrowClientArea()
	{
		int pos_x = sliderBarClientArea().x + sliderArrowMargin();
		int pos_y = sliderBarClientArea().y + sliderBarClientArea().h - sliderArrowHeight() - sliderArrowMargin();
		return SDL_Rect{ pos_x, pos_y, sliderArrowWidth(), sliderArrowHeight() };
	}

	template<class T, int C, int R>
	inline SDL_Rect SDLDataGrid<T, C, R>::sliderBarUpArrowClientArea()
	{
		int pos_x = sliderBarClientArea().x + sliderArrowMargin();
		int pos_y = sliderBarClientArea().y + sliderArrowMargin();
		return SDL_Rect{ pos_x, pos_y, sliderArrowWidth(), sliderArrowHeight() };
	}

	template<class T, int C, int R>
	inline int SDLDataGrid<T, C, R>::cellHeight()
	{
		return client_area_.h / R;
	}

	template<class T, int C, int R>
	inline int SDLDataGrid<T, C, R>::cellWidth()
	{
		return client_area_.w / C;
	}
}
