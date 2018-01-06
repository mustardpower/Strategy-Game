#pragma once

#include "DataGridCell.h"

namespace global_domination
{
	template <class T>
	class NoArgumentsGridCell : public DataGridCell<T>
	{
	public:
		NoArgumentsGridCell() {};
		NoArgumentsGridCell(std::shared_ptr<Action> an_action, T menu_item_data) : DataGridCell(an_action, menu_item_data)
		{
		}

	private:
		std::shared_ptr<Action> action_;
		SDL_Color text_color_;
		std::shared_ptr<SDL_Rect> text_location_;
		T data_;
	};
}