#define _CRT_SECURE_NO_WARNINGS

#include "FinanceHistory.h"

#include <assert.h>
#include <time.h>

namespace global_domination
{
	void FinanceHistory::addMonthlyHistory(MonthlyFinanceHistory history_point)
	{
		monthly_history_.push_back(history_point);
	}

	std::vector<double> FinanceHistory::getMonthlyBalanceHistory(unsigned int number_of_months)
	{
		std::vector<double> balance_history;
		double balance = 0.0;
		for (size_t i = 0; i < number_of_months; i++)
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

	std::vector<double> FinanceHistory::getMonthlyExpenditure(unsigned int number_of_months)
	{
		std::vector<double> expenditure_history;
		double balance = 0.0;
		for (size_t i = 0; i < number_of_months; i++)
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

	std::vector<double> FinanceHistory::getMonthlyProfits(unsigned int number_of_months)
	{
		std::vector<double> profit_history;
		double balance = 0.0;
		for (size_t i = 0; i < number_of_months; i++)
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

	std::vector<double> FinanceHistory::getMonthlyTaxIncome(unsigned int number_of_months)
	{
		std::vector<double> tax_income_history;
		double balance = 0.0;
		for (size_t i = 0; i < number_of_months; i++)
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

	std::vector<double> FinanceHistory::getMonthlyTradeDealsIncome(unsigned int number_of_months)
	{
		std::vector<double> trade_income_history;
		double balance = 0.0;
		for (size_t i = 0; i < number_of_months; i++)
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

	std::vector<double> FinanceHistory::getMonthlyTurnover(unsigned int number_of_months)
	{
		std::vector<double> turnover_history;
		double balance = 0.0;
		for (size_t i = 0; i < number_of_months; i++)
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
	double FinanceHistory::getExpenditureLastMonth() const
	{
		if (monthly_history_.empty()) { return 0.0; }
		return (monthly_history_.end() - 1)->expenditure_;
	}
	double FinanceHistory::getExpenditureThisYear() const
	{
		double expenditure = 0.0;

		if (monthly_history_.empty()) { return expenditure; }
		time_t last_months_date = (monthly_history_.end() - 1)->date_;
		int year_index = localtime(&last_months_date)->tm_year;

		for (std::vector<MonthlyFinanceHistory>::const_iterator month = monthly_history_.begin(); month != monthly_history_.end(); month++)
		{
			if (localtime(&month->date_)->tm_year == year_index)
			{
				expenditure += month->expenditure_;
			}
		}

		return expenditure;
	}
	double FinanceHistory::getExpenditureLastYear() const
	{
		double expenditure = 0.0;

		if (monthly_history_.empty()) { return expenditure; }
		time_t last_months_date = (monthly_history_.end() - 1)->date_;
		int year_index = localtime(&last_months_date)->tm_year;

		for (std::vector<MonthlyFinanceHistory>::const_iterator month = monthly_history_.begin(); month != monthly_history_.end(); month++)
		{
			if (localtime(&month->date_)->tm_year == year_index - 1)
			{
				expenditure += month->expenditure_;
			}
		}

		return expenditure;
	}
	double FinanceHistory::getIncomeLastMonth() const
	{
		if (monthly_history_.empty()) { return 0.0; }
		return (monthly_history_.end() - 1)->turnover_;
	}
	double FinanceHistory::getIncomeThisYear() const
	{
		double income = 0.0;

		if (monthly_history_.empty()) { return income; }
		time_t last_months_date = (monthly_history_.end() - 1)->date_;
		int year_index = localtime(&last_months_date)->tm_year;

		for (std::vector<MonthlyFinanceHistory>::const_iterator month = monthly_history_.begin(); month != monthly_history_.end(); month++)
		{
			if (localtime(&month->date_)->tm_year == year_index)
			{
				income += month->turnover_;
			}
		}

		return income;
	}
	double FinanceHistory::getIncomeLastYear() const
	{
		double income = 0.0;

		if (monthly_history_.empty()) { return income; }
		time_t last_months_date = (monthly_history_.end() - 1)->date_;
		int year_index = localtime(&last_months_date)->tm_year;

		for (std::vector<MonthlyFinanceHistory>::const_iterator month = monthly_history_.begin(); month != monthly_history_.end(); month++)
		{
			if (localtime(&month->date_)->tm_year == year_index - 1)
			{
				income += month->turnover_;
			}
		}

		return income;
	}
	double FinanceHistory::getProfitLastMonth() const
	{
		if (monthly_history_.empty()) { return 0.0; }
		return (monthly_history_.end() - 1)->profit_;
	}
	double FinanceHistory::getProfitThisYear() const
	{
		double profit = 0.0;

		if (monthly_history_.empty()) { return profit; }
		time_t last_months_date = (monthly_history_.end() - 1)->date_;
		int year_index = localtime(&last_months_date)->tm_year;

		for (std::vector<MonthlyFinanceHistory>::const_iterator month = monthly_history_.begin(); month != monthly_history_.end(); month++)
		{
			if (localtime(&month->date_)->tm_year == year_index)
			{
				profit += month->profit_;
			}
		}

		return profit;
	}
	double FinanceHistory::getProfitLastYear() const
	{
		double profit = 0.0;

		if (monthly_history_.empty()) { return profit; }
		time_t last_months_date = (monthly_history_.end() - 1)->date_;
		int year_index = localtime(&last_months_date)->tm_year;

		for (std::vector<MonthlyFinanceHistory>::const_iterator month = monthly_history_.begin(); month != monthly_history_.end(); month++)
		{
			if (localtime(&month->date_)->tm_year == year_index - 1)
			{
				profit += month->profit_;
			}
		}

		return profit;
	}
	double FinanceHistory::getTaxIncomeLastMonth() const
	{
		if (monthly_history_.empty()) { return 0.0; }
		return (monthly_history_.end() - 1)->tax_income_;
	}
	double FinanceHistory::getTaxIncomeLastYear() const
	{
		double tax_income = 0.0;

		if (monthly_history_.empty()) { return tax_income; }
		time_t last_months_date = (monthly_history_.end() - 1)->date_;
		int year_index = localtime(&last_months_date)->tm_year;

		for (std::vector<MonthlyFinanceHistory>::const_iterator month = monthly_history_.begin(); month != monthly_history_.end(); month++)
		{
			if (localtime(&month->date_)->tm_year == year_index - 1)
			{
				tax_income += month->tax_income_;
			}
		}

		return tax_income;
	}
	double FinanceHistory::getTaxIncomeThisYear() const
	{
		double tax_income = 0.0;

		// get last item in monthly_history
		if (monthly_history_.empty()) { return tax_income; }
		time_t last_months_date = (monthly_history_.end() - 1)->date_;

		// look at the year
		int last_month_index = localtime(&last_months_date)->tm_mon;
		if (last_month_index == 12) { return tax_income; }

		int year_index = localtime(&last_months_date)->tm_year;

		// go through any entries with same year and sum the trade income
		for (std::vector<MonthlyFinanceHistory>::const_iterator month = monthly_history_.begin(); month != monthly_history_.end(); month++)
		{
			if (localtime(&month->date_)->tm_year == year_index)
			{
				tax_income += month->tax_income_;
			}
		}


		return tax_income;
	}
	double FinanceHistory::getTradeIncomeLastMonth() const
	{
		if (monthly_history_.empty()) { return 0.0; }
		return (monthly_history_.end() - 1)->trade_income_;
	}

	double FinanceHistory::getTradeIncomeLastYear() const
	{
		double trade_income = 0.0;

		// get last item in monthly_history
		if (monthly_history_.empty()) { return trade_income; }
		time_t last_months_date = (monthly_history_.end() - 1)->date_;
		int year_index = localtime(&last_months_date)->tm_year;

		// go through any entries with same year and sum the trade income
		for (std::vector<MonthlyFinanceHistory>::const_iterator month = monthly_history_.begin(); month != monthly_history_.end(); month++)
		{
			if (localtime(&month->date_)->tm_year == year_index - 1)
			{
				trade_income += month->trade_income_;
			}
		}

		return trade_income;
	}

	double FinanceHistory::getTradeIncomeThisYear() const
	{
		double trade_income = 0.0;

		// get last item in monthly_history
		if (monthly_history_.empty()) { return trade_income; }
		time_t last_months_date = (monthly_history_.end() - 1)->date_;

		// look at the year
		int last_month_index = localtime(&last_months_date)->tm_mon;
		if (last_month_index == 12) { return trade_income; }

		int year_index = localtime(&last_months_date)->tm_year;

		// go through any entries with same year and sum the trade income
		for (std::vector<MonthlyFinanceHistory>::const_iterator month = monthly_history_.begin(); month != monthly_history_.end(); month++)
		{
			if (localtime(&month->date_)->tm_year == year_index)
			{
				trade_income += month->trade_income_;
			}
		}
		

		return trade_income;
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
