#pragma once

#include <vector>

namespace global_domination
{
	class FinanceHistory
	{
	public:
		void addMonthlyBalance(double monthly_balance);
		void addMonthlyExpenditure(double monthly_expenditure);
		void addMonthlyProfit(double monthly_profit);
		void addMonthlyTurnover(double monthly_turnover);
		std::vector<double> getMonthlyBalanceHistory(int number_of_months);
		std::vector<double> getMonthlyExpenditure(int number_of_months);
		std::vector<double> getMonthlyProfits(int number_of_months);
		std::vector<double> getMonthlyTurnover(int number_of_months);
	private:
		std::vector<double> monthly_balance_;
		std::vector<double> monthly_expenditure_;
		std::vector<double> monthly_profits_;
		std::vector<double> monthly_turnover_;
	};
}