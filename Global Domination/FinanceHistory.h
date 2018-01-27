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
		std::vector<double> getMonthlyBalanceHistory(unsigned int number_of_months);
		std::vector<double> getMonthlyExpenditure(unsigned int number_of_months);
		std::vector<double> getMonthlyProfits(unsigned int number_of_months);
		std::vector<double> getMonthlyTaxIncome(unsigned int number_of_months);
		std::vector<double> getMonthlyTradeDealsIncome(unsigned int number_of_months);
		std::vector<double> getMonthlyTurnover(unsigned int number_of_months);
		double getExpenditureLastMonth() const;
		double getExpenditureThisYear() const;
		double getExpenditureLastYear() const;
		double getIncomeLastMonth() const;
		double getIncomeThisYear() const;
		double getIncomeLastYear() const;
		double getProfitLastMonth() const;
		double getProfitThisYear() const;
		double getProfitLastYear() const;
		double getTaxIncomeLastMonth() const;
		double getTaxIncomeLastYear() const;
		double getTaxIncomeThisYear() const;
		double getTradeIncomeLastMonth() const;
		double getTradeIncomeLastYear() const;
		double getTradeIncomeThisYear() const;
	private:
		std::vector<MonthlyFinanceHistory> monthly_history_;
	};
}