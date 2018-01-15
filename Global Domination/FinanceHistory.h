#pragma once

#include <vector>

namespace global_domination
{
	class FinanceHistory
	{
	public:
		void addMonthlyProfit(double monthly_profit);
		void addMonthlyBalance(double monthly_balance);
		std::vector<double> getMonthlyBalanceHistory(int number_of_months);
		std::vector<double> getMonthlyProfits(int number_of_months);
	private:
		std::vector<double> monthly_balance_;
		std::vector<double> monthly_profits_;
	};
}