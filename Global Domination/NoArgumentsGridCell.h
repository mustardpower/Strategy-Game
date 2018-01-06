#pragma once

#include "DataGridCell.h"

namespace global_domination
{
	template <class T>
	class NoArgumentsGridCell : public DataGridCell<T>
	{
	public:
		NoArgumentsGridCell() {};
		NoArgumentsGridCell(std::shared_ptr<Action> an_action, T menu_item_data, std::function<std::string(const T&)> selector) : DataGridCell(an_action, menu_item_data)
		{
			selector_ = selector;
		}

		std::string reportString() const;

	private:
		std::function<std::string(const T&)> selector_;
	};
	
	template<class T>
	inline std::string NoArgumentsGridCell<T>::reportString() const
	{
		return selector_(data_);
	}
}