#include "FinanceHistory.h"

namespace global_domination
{
	void FinanceHistory::addMonthlyProfit(double monthly_profit)
	{
		monthly_profits_.push_back(monthly_profit);
	}

	void FinanceHistory::addMonthlyTurnover(double monthly_turnover)
	{
		monthly_turnover_.push_back(monthly_turnover);
	}

	void FinanceHistory::addMonthlyBalance(double monthly_balance)
	{
		monthly_balance_.push_back(monthly_balance);
	}

	void FinanceHistory::addMonthlyExpenditure(double monthly_expenditure)
	{
		monthly_expenditure_.push_back(monthly_expenditure);
	}

	std::vector<double> FinanceHistory::getMonthlyBalanceHistory(int number_of_months)
	{
		std::vector<double>::const_iterator first;
		if (monthly_balance_.size() < number_of_months)
		{
			first = monthly_balance_.begin();
		}
		else
		{
			first = monthly_balance_.end() - number_of_months;
		}

		std::vector<double>::const_iterator last = monthly_balance_.end();
		return std::vector<double>(first, last);
	}

	std::vector<double> FinanceHistory::getMonthlyExpenditure(int number_of_months)
	{
		std::vector<double>::const_iterator first;
		if (monthly_expenditure_.size() < number_of_months)
		{
			first = monthly_expenditure_.begin();
		}
		else
		{
			first = monthly_expenditure_.end() - number_of_months;
		}

		std::vector<double>::const_iterator last = monthly_expenditure_.end();
		return std::vector<double>(first, last);
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

	std::vector<double> FinanceHistory::getMonthlyTurnover(int number_of_months)
	{
		std::vector<double>::const_iterator first;
		if (monthly_turnover_.size() < number_of_months)
		{
			first = monthly_turnover_.begin();
		}
		else
		{
			first = monthly_turnover_.end() - number_of_months;
		}

		std::vector<double>::const_iterator last = monthly_turnover_.end();
		return std::vector<double>(first, last);
	}
}
