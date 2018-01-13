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

		void setString(std::string reported_string);
		std::string reportString() const;

	private:
		std::function<std::string(const T&)> selector_;
		std::string string_override_;
	};
	
	template<class T>
	inline void NoArgumentsGridCell<T>::setString(std::string reported_string)
	{
		string_override_ = reported_string;
	}

	template<class T>
	inline std::string NoArgumentsGridCell<T>::reportString() const
	{
		if (!string_override_.empty())
		{
			return string_override_;
		}

		return selector_(data_);
	}
}