#include "FinanceHistory.h"

namespace global_domination
{
	void FinanceHistory::addMonthlyProfit(double monthly_profit)
	{
		monthly_profits_.push_back(monthly_profit);
	}
	std::vector<double> FinanceHistory::getMonthlyProfits(int number_of_months)
	{
		std::vector<double>::const_iterator first;
		if (monthly_profits_.size() < number_of_months)
		{
			first = monthly_profits_.begin();
		}
		else
		{
			first = monthly_profits_.end() - number_of_months;
		}
		
		std::vector<double>::const_iterator last = monthly_profits_.end();
		return std::vector<double>(first, last);
	}
}
