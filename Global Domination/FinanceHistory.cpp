#include "FinanceHistory.h"

namespace global_domination
{
	void FinanceHistory::addMonthlyHistory(MonthlyFinanceHistory history_point)
	{
		monthly_history_.push_back(history_point);
	}

	std::vector<double> FinanceHistory::getMonthlyBalanceHistory(int number_of_months)
	{
		return std::vector<double>();
	}

	std::vector<double> FinanceHistory::getMonthlyExpenditure(int number_of_months)
	{
		return std::vector<double>();
	}

	std::vector<double> FinanceHistory::getMonthlyProfits(int number_of_months)
	{
		return std::vector<double>();
	}

	std::vector<double> FinanceHistory::getMonthlyTaxIncome(int number_of_months)
	{
		return std::vector<double>();
	}

	std::vector<double> FinanceHistory::getMonthlyTradeDealsIncome(int number_of_months)
	{
		return std::vector<double>();
	}

	std::vector<double> FinanceHistory::getMonthlyTurnover(int number_of_months)
	{
		return std::vector<double>();
	}
	MonthlyFinanceHistory::MonthlyFinanceHistory(time_t date, double balance, double expenditure, double tax_income, double trade_income, double profit, double turnover)
	{
		date_ = date;
		balance_ = balance;
		expenditure_ = expenditure;
		tax_income_ = tax_income;
		trade_income_ = trade_income;
		profit_ = profit;
		turnover_ = turnover;
	}
}
