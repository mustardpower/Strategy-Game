#include "FinanceHistory.h"

#include <assert.h>

namespace global_domination
{
	void FinanceHistory::addMonthlyHistory(MonthlyFinanceHistory history_point)
	{
		monthly_history_.push_back(history_point);
	}

	std::vector<double> FinanceHistory::getMonthlyBalanceHistory(int number_of_months)
	{
		std::vector<double> balance_history;
		double balance = 0.0;
		for (int i = 0; i < number_of_months; i++)
		{
			if (monthly_history_.size() < number_of_months - i)
			{
				balance_history.push_back(balance);
			}
			else
			{
				std::vector<MonthlyFinanceHistory>::iterator history = monthly_history_.end() - (number_of_months - i);
				balance = (*history).balance_;
				balance_history.push_back(balance);
			}
		}

		assert(balance_history.size() == number_of_months);
		return balance_history;
	}

	std::vector<double> FinanceHistory::getMonthlyExpenditure(int number_of_months)
	{
		std::vector<double> expenditure_history;
		double balance = 0.0;
		for (int i = 0; i < number_of_months; i++)
		{
			if (monthly_history_.size() < number_of_months - i)
			{
				expenditure_history.push_back(balance);
			}
			else
			{
				std::vector<MonthlyFinanceHistory>::iterator history = monthly_history_.end() - (number_of_months - i);
				balance = (*history).expenditure_;
				expenditure_history.push_back(balance);
			}
		}

		assert(expenditure_history.size() == number_of_months);
		return expenditure_history;
	}

	std::vector<double> FinanceHistory::getMonthlyProfits(int number_of_months)
	{
		std::vector<double> profit_history;
		double balance = 0.0;
		for (int i = 0; i < number_of_months; i++)
		{
			if (monthly_history_.size() < number_of_months - i)
			{
				profit_history.push_back(balance);
			}
			else
			{
				std::vector<MonthlyFinanceHistory>::iterator history = monthly_history_.end() - (number_of_months - i);
				balance = (*history).profit_;
				profit_history.push_back(balance);
			}
		}

		assert(profit_history.size() == number_of_months);
		return profit_history;
	}

	std::vector<double> FinanceHistory::getMonthlyTaxIncome(int number_of_months)
	{
		std::vector<double> tax_income_history;
		double balance = 0.0;
		for (int i = 0; i < number_of_months; i++)
		{
			if (monthly_history_.size() < number_of_months - i)
			{
				tax_income_history.push_back(balance);
			}
			else
			{
				std::vector<MonthlyFinanceHistory>::iterator history = monthly_history_.end() - (number_of_months - i);
				balance = (*history).tax_income_;
				tax_income_history.push_back(balance);
			}
		}

		assert(tax_income_history.size() == number_of_months);
		return tax_income_history;
	}

	std::vector<double> FinanceHistory::getMonthlyTradeDealsIncome(int number_of_months)
	{
		std::vector<double> trade_income_history;
		double balance = 0.0;
		for (int i = 0; i < number_of_months; i++)
		{
			if (monthly_history_.size() < number_of_months - i)
			{
				trade_income_history.push_back(balance);
			}
			else
			{
				std::vector<MonthlyFinanceHistory>::iterator history = monthly_history_.end() - (number_of_months - i);
				balance = (*history).trade_income_;
				trade_income_history.push_back(balance);
			}
		}

		assert(trade_income_history.size() == number_of_months);
		return trade_income_history;
	}

	std::vector<double> FinanceHistory::getMonthlyTurnover(int number_of_months)
	{
		std::vector<double> turnover_history;
		double balance = 0.0;
		for (int i = 0; i < number_of_months; i++)
		{
			if (monthly_history_.size() < number_of_months - i)
			{
				turnover_history.push_back(balance);
			}
			else
			{
				std::vector<MonthlyFinanceHistory>::iterator history = monthly_history_.end() - (number_of_months - i);
				balance = (*history).turnover_;
				turnover_history.push_back(balance);
			}
		}

		assert(turnover_history.size() == number_of_months);
		return turnover_history;
	}
	double FinanceHistory::getTradeIncomeLastMonth() const
	{
		if (monthly_history_.empty()) { return 0.0; }
		return (monthly_history_.end() - 1)->trade_income_;
	}

	double FinanceHistory::getTradeIncomeLastYear() const
	{
		return 0.0;
	}

	double FinanceHistory::getTradeIncomeThisYear() const
	{
		return 0.0;
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
