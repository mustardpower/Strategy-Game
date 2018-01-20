#pragma once

#include "DataGridCell.h"

namespace global_domination
{
	template <class T>
	class NoArgumentsGridCell : public DataGridCell
	{
	public:
		NoArgumentsGridCell() {};
		NoArgumentsGridCell(std::shared_ptr<Action> an_action, const T& cell_data, std::function<std::string(const T&)> selector) : DataGridCell(an_action), data_(cell_data)
		{
			selector_ = selector;
		}

		const T& getData();
		std::string reportString() const;

	private:
		const T& data_;
		std::function<std::string(const T&)> selector_;
	};

	template<class T>
	inline const T& NoArgumentsGridCell<T>::getData()
	{
		return data_;
	}

	template<class T>
	inline std::string NoArgumentsGridCell<T>::reportString() const
	{
		return selector_(data_);
	}
}