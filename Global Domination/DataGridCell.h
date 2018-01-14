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
		virtual std::string reportString() const = 0;
		void setAction(std::shared_ptr<Action> an_action);

		DataGridCell(std::shared_ptr<Action> an_action, T menu_item_data)
		{
			action_ = an_action;
			data_ = menu_item_data;
		}

	protected:
		T data_;
	private:
		std::shared_ptr<Action> action_;
		SDL_Color text_color_;
		std::shared_ptr<SDL_Rect> text_location_;
	};

	template<class T>
	inline T * DataGridCell<T>::getData()
	{
		return &data_;
	}

	template<class T>
	inline void DataGridCell<T>::invokeAction() const
	{
		if (action_)
		{
			action_->execute();
		}
	}

	template<class T>
	inline void DataGridCell<T>::setAction(std::shared_ptr<Action> an_action)
	{
		action_ = an_action;
	}
}