#include "FinanceHistory.h"

namespace global_domination
{
	void FinanceHistory::addMonthlyProfit(double monthly_profit)
	{
		monthly_profits_.push_back(monthly_profit);
	}

	void FinanceHistory::addMonthlyTaxIncome(double monthly_income)
	{
		monthly_tax_income_.push_back(monthly_income);
	}

	void FinanceHistory::addMonthlyTradeDealsIncome(double monthly_income)
	{
		monthly_tradedeals_income_.push_back(monthly_income);
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

	std::vector<double> FinanceHistory::getMonthlyTaxIncome(int number_of_months)
	{
		std::vector<double>::const_iterator first;
		if (monthly_tax_income_.size() < number_of_months)
		{
			first = monthly_tax_income_.begin();
		}
		else
		{
			first = monthly_tax_income_.end() - number_of_months;
		}

		std::vector<double>::const_iterator last = monthly_tax_income_.end();
		return std::vector<double>(first, last);
	}

	std::vector<double> FinanceHistory::getMonthlyTradeDealsIncome(int number_of_months)
	{
		std::vector<double>::const_iterator first;
		if (monthly_tradedeals_income_.size() < number_of_months)
		{
			first = monthly_tradedeals_income_.begin();
		}
		else
		{
			first = monthly_tradedeals_income_.end() - number_of_months;
		}

		std::vector<double>::const_iterator last = monthly_tradedeals_income_.end();
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
