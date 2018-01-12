#pragma once

#include <vector>

namespace global_domination
{
	class FinanceHistory
	{
	public:
		void addMonthlyProfit(double monthly_profit);
		std::vector<double> getMonthlyProfits(int number_of_months);
	private:
		std::vector<double> monthly_profits_;
	};
}