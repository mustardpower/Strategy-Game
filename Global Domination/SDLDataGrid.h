#pragma once

#include "SDL.h"
#include "SDL2_gfxPrimitives.h"

#include <functional>

#include "ColorPreferences.h"
#include "DataGridCell.h"
#include "NoArgumentsGridCell.h"
#include "SDL_TextRenderer.h"

namespace global_domination
{
	template <class T, int C, int R>
	class SDLDataGrid : public SDLControl
	{
	public:
		SDLDataGrid(SDL_Window* parent, SDL_Rect client_area, std::array<std::string, C> header_names_);
		~SDLDataGrid();
		void addItem(std::string item_string, int location_x, int location_y, TYPES::ACTION_LIST action);
		void addItem(std::shared_ptr<DataGridCell<T>> item, int location_x, int location_y);
		SDL_Rect cellClientArea(int column, int row);
		int cellHeight();
		int cellWidth();
		bool containsPoint(SDL_Rect aRect, int x, int y);
		void drawGridLines(SDL_Renderer* renderer);
		void drawSliderBar(SDL_Renderer* renderer);
		void drawSliderBarUpArrow(SDL_Renderer* renderer);
		void drawSliderBarDownArrow(SDL_Renderer* renderer);
		bool handleClick(int x, int y);
		SDL_Rect headerClientArea(int column);
		int headerHeight();
		void render(SDL_Renderer * renderer);
		void renderCells(SDL_Renderer * renderer);
		void renderCell(SDL_Renderer* renderer, int column, int row);
		void renderHeaderCells(SDL_Renderer* renderer);
		const int sliderArrowHeight();
		const int sliderArrowMargin();
		const int sliderArrowWidth();
		SDL_Rect sliderBarClientArea();
		SDL_Rect sliderBarDownArrowClientArea();
		SDL_Rect sliderBarUpArrowClientArea();
		void showSliderBar(bool shown);
	private:
		SDL_Rect client_area_;
		std::array<std::string, C> header_names_;
		std::array<std::vector<std::shared_ptr<DataGridCell<T>>>, C> items_;
		unsigned int selected_index_;
		bool show_slider_bar_;
		unsigned int top_visible_index_;
	};

	template <class T, int C, int R>
	inline SDLDataGrid<T, C, R>::SDLDataGrid(SDL_Window * parent, SDL_Rect client_area, std::array<std::string, C> header_names) : SDLControl(parent, client_area)
	{
		client_area_ = client_area;
		header_names_ = header_names;
		selected_index_ = 0;
		show_slider_bar_ = true;
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
	inline void SDLDataGrid<T, C, R>::addItem(std::string item_string, int column, int row, TYPES::ACTION_LIST action_type)
	{
		std::shared_ptr<NoArgumentsGridCell<T>> item = std::make_shared<NoArgumentsGridCell<T>>();
		std::shared_ptr<Action> action = std::make_shared<Action>(action_type);
		item->setAction(action);
		item->setString(item_string);
		items_[column].push_back(item);
	}

	template<class T, int C, int R>
	inline SDL_Rect SDLDataGrid<T, C, R>::cellClientArea(int column, int row)
	{
		return SDL_Rect { client_area_.x + (column * cellWidth()), client_area_.y + row * cellHeight() + headerHeight(), cellWidth(), cellHeight() };
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

	template<class T, int C, int R>
	inline void SDLDataGrid<T, C, R>::drawGridLines(SDL_Renderer * renderer)
	{
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xFF);
		for (size_t column = 0; column < items_.size(); column++)
		{
			SDL_RenderDrawLine(renderer, client_area_.x + (column * cellWidth()), client_area_.y, client_area_.x + (column * cellWidth()), client_area_.y + client_area_.h);

			for (int grid_row = 0; grid_row < R + 1; grid_row++)
			{
				int line_height = client_area_.y + headerHeight() + (grid_row * cellHeight());
				SDL_RenderDrawLine(renderer, client_area_.x, line_height, client_area_.x + client_area_.w, line_height);
			}
		}
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
			up_arrow_client_area.x + (int)(up_arrow_client_area.w * 0.05), up_arrow_client_area.y + up_arrow_client_area.h,
			up_arrow_client_area.x + (int)(up_arrow_client_area.w / 2), up_arrow_client_area.y,
			up_arrow_client_area.x + (int)(up_arrow_client_area.w * 0.95), up_arrow_client_area.y + up_arrow_client_area.h,
			0, 0, 0, 255);
	}

	template <class T, int C, int R>
	inline void SDLDataGrid<T, C, R>::drawSliderBarDownArrow(SDL_Renderer * renderer)
	{
		SDL_Rect down_arrow_client_area = sliderBarDownArrowClientArea();
		filledTrigonRGBA(renderer,
			down_arrow_client_area.x + (int)(down_arrow_client_area.w * 0.05), down_arrow_client_area.y,
			down_arrow_client_area.x + (int)(down_arrow_client_area.w / 2), down_arrow_client_area.y + down_arrow_client_area.h,
			down_arrow_client_area.x + (int)(down_arrow_client_area.w * 0.95), down_arrow_client_area.y,
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

		for (unsigned int i = 0; i < items_.size(); i++)
		{
			for (unsigned int j = 0; j < items_[i].size(); j++)
			{
				SDL_Rect text_location = SDL_Rect{ client_area_.x + ((int)i * cellWidth()), client_area_.y + headerHeight() + ((int)j * cellHeight()), cellWidth(), cellHeight() };
				if (containsPoint(text_location, x, y))
				{
					selected_index_ = j + top_visible_index_;
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

	template<class T, int C, int R>
	inline SDL_Rect SDLDataGrid<T, C, R>::headerClientArea(int column)
	{
		return SDL_Rect{ client_area_.x + (column * cellWidth()), client_area_.y, cellWidth(), headerHeight() };
	}

	template<class T, int C, int R>
	inline int SDLDataGrid<T, C, R>::headerHeight()
	{
		int target_height = (int)(client_area_.h * 0.15);
		int overall_height = target_height + R * cellHeight();
		if (overall_height != client_area_.h)
		{
			int difference = client_area_.h - overall_height;
			return target_height + difference;
		}
		return target_height;
	}

	template <class T, int C, int R>
	inline void SDLDataGrid<T, C, R>::render(SDL_Renderer * renderer)
	{
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0xFF);
		SDL_RenderFillRect(renderer, &client_area_);

		renderHeaderCells(renderer);
		renderCells(renderer);
		drawGridLines(renderer);

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xFF);
		SDL_RenderDrawRect(renderer, &client_area_);

		if (show_slider_bar_)
		{
			drawSliderBar(renderer);
		}
	}

	template<class T, int C, int R>
	inline void SDLDataGrid<T, C, R>::renderCells(SDL_Renderer * renderer)
	{
		for (size_t column = 0; column < items_.size(); column++)
		{
			for (int grid_row = 0; grid_row < R; grid_row++)
			{
				const unsigned int item_index = grid_row + top_visible_index_;
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
		const int item_index = grid_row + top_visible_index_;
		if (selected_index_ == item_index)
		{
			SDL_SetRenderDrawColor(renderer, 255, 100, 100, 0xFF);
		}
		else
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0xFF);
		}

		SDL_RenderFillRect(renderer, &cellClientArea(column, grid_row));

		std::string text = items_[column][item_index]->reportString();
		SDL_Rect text_location = text_renderer::getCenteredTextLocation(cellClientArea(column, grid_row), text, font_size_);
		global_domination::text_renderer::renderText(parent_, text, text_location, ColorPreferences::getPrimaryTextColor(), SDL_Color{ 0,0,0,0xFF }, 15);
	}

	template<class T, int C, int R>
	inline void SDLDataGrid<T, C, R>::renderHeaderCells(SDL_Renderer * renderer)
	{
		for (size_t column = 0; column < items_.size(); column++)
		{
			SDL_SetRenderDrawColor(renderer, 200, 200, 200, 0xFF);
			SDL_RenderFillRect(renderer, &headerClientArea(column));
			SDL_Color text_color = ColorPreferences::getPrimaryTextColor();
			SDL_Rect text_location = text_renderer::getCenteredTextLocation(headerClientArea(column), header_names_[column], font_size_);
			global_domination::text_renderer::renderText(parent_, header_names_[column], text_location, text_color, SDL_Color{ 0,0,0,0xFF }, 15);
		}
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
	inline void SDLDataGrid<T, C, R>::showSliderBar(bool shown)
	{
		show_slider_bar_ = shown;
	}

	template<class T, int C, int R>
	inline int SDLDataGrid<T, C, R>::cellHeight()
	{
		return (client_area_.h - (int)(client_area_.h * 0.15)) / R;
	}

	template<class T, int C, int R>
	inline int SDLDataGrid<T, C, R>::cellWidth()
	{
		return client_area_.w / C;
	}
}
