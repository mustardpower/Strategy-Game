#pragma once

#include <vector>

namespace global_domination
{
	struct MonthlyFinanceHistory
	{
		MonthlyFinanceHistory() {};
		MonthlyFinanceHistory(time_t date, double balance, double expenditure, double tax_income, double trade_income, double profit, double turnover);

		time_t date_;
		double balance_;
		double expenditure_;
		double tax_income_;
		double trade_income_;
		double profit_;
		double turnover_;
	};

	class FinanceHistory
	{
	public:
		void addMonthlyHistory(MonthlyFinanceHistory history_point);
		std::vector<double> getMonthlyBalanceHistory(int number_of_months);
		std::vector<double> getMonthlyExpenditure(int number_of_months);
		std::vector<double> getMonthlyProfits(int number_of_months);
		std::vector<double> getMonthlyTaxIncome(int number_of_months);
		std::vector<double> getMonthlyTradeDealsIncome(int number_of_months);
		std::vector<double> getMonthlyTurnover(int number_of_months);
		double getTradeIncomeLastMonth() const;
		double getTradeIncomeLastYear() const;
		double getTradeIncomeThisYear() const;
	private:
		std::vector<MonthlyFinanceHistory> monthly_history_;
	};
}