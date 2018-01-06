#pragma once

#include "Action.h"

namespace global_domination
{
	template <class T>
	class DataGridCell
	{
	public:
		DataGridCell() {};
		T* getData();
		void invokeAction() const;
		std::string reportString() const;

		DataGridCell(std::shared_ptr<Action> an_action, T menu_item_data)
		{
			action_ = an_action;
			data_ = menu_item_data;
		}

	private:
		std::shared_ptr<Action> action_;
		SDL_Color text_color_;
		std::shared_ptr<SDL_Rect> text_location_;
		T data_;
	};

	template<class T>
	inline T * DataGridCell<T>::getData()
	{
		return &data_;
	}

	template<class T>
	inline void DataGridCell<T>::invokeAction() const
	{
		action_->execute();
	}

	template<class T>
	inline std::string DataGridCell<T>::reportString() const
	{
		return data_.reportString();
	}

}