#pragma once

#include "DataGridCell.h"

namespace global_domination
{
	template <class T, class Arg>
	class OneArgumentGridCell : public DataGridCell<T>
	{
	public:
		OneArgumentGridCell() {};
		OneArgumentGridCell(std::shared_ptr<Action> an_action, T menu_item_data, Arg selector_argument, std::function<std::string(const T&, Arg)> selector) : DataGridCell(an_action, menu_item_data), selector_argument_(selector_argument)
		{
			selector_ = selector;
		}

		std::string reportString() const;

	private:
		std::function<std::string(const T&, Arg)> selector_;
		Arg selector_argument_;
	};

	template<class T, class Arg>
	inline std::string OneArgumentGridCell<T, Arg>::reportString() const
	{
		return selector_(data_, selector_argument_);
	}
}