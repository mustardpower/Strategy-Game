#pragma once

#include "DataGridCell.h"

#include <string>

namespace global_domination
{
	class StringDataCell : public DataGridCell
	{
	public:
		std::string reportString() const;
		void setString(std::string reported_string);
	private:
		std::string data_;
	};

	inline std::string StringDataCell::reportString() const
	{
		return data_;
	}

	inline void StringDataCell::setString(std::string reported_string)
	{
		data_ = reported_string;
	}
}