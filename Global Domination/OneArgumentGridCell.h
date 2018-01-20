#pragma once

#include "DataGridCell.h"

namespace global_domination
{
	template <class T, class Arg>
	class OneArgumentGridCell : public DataGridCell
	{
	public:
		OneArgumentGridCell() {};
		OneArgumentGridCell(std::shared_ptr<Action> an_action, const T& cell_data, Arg selector_argument, std::function<std::string(const T&, Arg)> selector) : DataGridCell(an_action), data_(cell_data), selector_argument_(selector_argument)
		{
			selector_ = selector;
		}

		const T& getData();
		std::string reportString() const;

	private:
		const T& data_;
		std::function<std::string(const T&, Arg)> selector_;
		Arg selector_argument_;
	};

	template<class T, class Arg>
	inline const T& OneArgumentGridCell<T, Arg>::getData()
	{
		return &data_;
	}

	template<class T, class Arg>
	inline std::string OneArgumentGridCell<T, Arg>::reportString() const
	{
		return selector_(data_, selector_argument_);
	}
}