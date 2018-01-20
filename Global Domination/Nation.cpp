
#include "Nation.h"
#include <fstream>

namespace global_domination
{
	Nation::Nation(std::string aName, double balance, int population, std::map<TradeResource, int> resources, std::vector<TradeDeal> trade_deals, double area)
	{
		area_ = area;
		average_salary_ = 27000;
		balance_ = balance;
		employment_rate_ = 1.0;
		name_ = aName;
		population_ = population;
		resources_ = resources;
		tax_rate_ = 0.0;
		trade_deals_ = trade_deals;
	}

	void Nation::acceptTradeOffer(TradeDeal trade_deal)
	{
		trade_offers_.erase(trade_deal);
		trade_deals_.push_back(trade_deal);
	}

	void Nation::declineTradeOffer(TradeDeal trade_deal)
	{
		trade_offers_.erase(trade_deal);
	}

	std::vector<Nation*> Nation::alliedNations()
	{
		std::vector<Nation*> allies;
		const double REQUIRED_ALLY_SCORE = 0.5;
		for (std::map<Nation*, double>::iterator relation = nation_friendships.begin(); relation != nation_friendships.end(); relation++)
		{
			if (relation->second >= REQUIRED_ALLY_SCORE)
			{
				allies.push_back(relation->first);
			}
		}
		return allies;
	}

	double Nation::calculateMonthlyExpenses() const
	{
		return 0.0;
	}

	double Nation::calculateMonthlyIncome() const
	{
		double income = 0.0;

		income += monthlyIncomeFromTradeDeals();
		income += monthlyIncomeFromTax();
		
		return income;
	}

	double Nation::calculateMonthlyProfit() const
	{
		return calculateMonthlyIncome() - calculateMonthlyExpenses();
	}

	void Nation::cancelTradeDeal(TradeDeal trade_deal)
	{
		std::vector<TradeDeal>::iterator matching_deal = std::find(trade_deals_.begin(), trade_deals_.end(), trade_deal);
		trade_deals_.erase(matching_deal);
	}

	double Nation::getBalance() const
	{
		return balance_;
	}

	double Nation::getBalancePerCapita() const
	{
		if (population_ == 0) { return 0; }
		return (balance_ / population_) * 1000000;
	}

	double Nation::getLandArea() const
	{
		return area_;
	}

	std::vector<double> Nation::getMonthlyBalanceHistory(int number_of_months)
	{
		return finance_history_.getMonthlyBalanceHistory(number_of_months);
	}

	std::vector<double> Nation::getMonthlyExpenditureHistory(int number_of_months)
	{
		return finance_history_.getMonthlyExpenditure(number_of_months);
	}

	std::vector<double> Nation::getMonthlyProfitsHistory(int number_of_months)
	{
		return finance_history_.getMonthlyProfits(number_of_months);
	}

	std::vector<double> Nation::getMonthlyTaxIncomeHistory(int number_of_months)
	{
		return finance_history_.getMonthlyTaxIncome(number_of_months);
	}

	std::vector<double> Nation::getMonthlyTradeDealsIncomeHistory(int number_of_months)
	{
		return finance_history_.getMonthlyTradeDealsIncome(number_of_months);
	}

	std::vector<double> Nation::getMonthlyTurnoverHistory(int number_of_months)
	{
		return finance_history_.getMonthlyTurnover(number_of_months);
	}

	std::string Nation::getName() const
	{
		return name_;
	}

	unsigned int Nation::getNumberOfDeathsInTurn() const
	{
		return 0;
	}

	unsigned int Nation::getNumberOfBirthsInTurn() const
	{
		return 0;
	}

	int Nation::getPopulation() const
	{
		return population_;
	}

	double Nation::getTaxRate() const
	{
		return tax_rate_;
	}

	std::map<TradeResource, int> Nation::getTradeableResources()
	{
		return resources_;
	}

	std::vector<TradeDeal> Nation::getTradeDeals() const
	{
		return trade_deals_;
	}

	std::vector<TradeDeal> Nation::getTradeDealsForResource(TradeResource resource)
	{
		std::vector<TradeDeal> matching_deals;
		for (std::vector<TradeDeal>::iterator deal = trade_deals_.begin(); deal != trade_deals_.end(); deal++)
		{
			if (deal->getResource() == resource)
			{
				matching_deals.push_back(*deal);
			}
		}

		return matching_deals;
	}

	std::vector<TradeDeal> Nation::getTradeOffersForResource(TradeResource resource)
	{
		std::vector<TradeDeal> matching_offers;
		for (std::set<TradeDeal>::iterator offer = trade_offers_.begin(); offer != trade_offers_.end(); offer++)
		{
			if (offer->getResource() == resource)
			{
				matching_offers.push_back(*offer);
			}
		}

		return matching_offers;
	}

	std::map<TradeResource, int> Nation::getTradeResources() const
	{
		return resources_;
	}

	// returns percentage of global area controlled - calculated in km sq
	double Nation::globalAreaPercentageControlled() const
	{
		const double kAreaOfWorld = 148940000;
		return (area_ / kAreaOfWorld) * 100;
	}

	void Nation::makeTradeDeals()
	{
		std::vector<Nation*> allies = alliedNations();
		for (std::vector<Nation*>::iterator nation = allies.begin(); nation != allies.end(); nation++)
		{
			std::map<TradeResource, int> wanted_resources = (*nation)->getTradeableResources();
			std::map<TradeResource, int> tradeable_resources = (*nation)->getTradeableResources();

			for (std::map<TradeResource, int>::iterator resource = tradeable_resources.begin(); resource != tradeable_resources.end(); resource++)
			{
				for (std::map<TradeResource, int>::iterator wanted = wanted_resources.begin(); wanted != wanted_resources.end(); wanted++)
				{
					if (wanted->first == resource->first)
					{
						TradeDeal prospective_trade_deal(name_, resource->first, resource->second);
						(*nation)->recieveTradeOffer(prospective_trade_deal);
					}
				}
			}
		}
	}

	double Nation::monthlyIncomeFromTax() const
	{
		const int kNumberOfMonths = 12;
		double average_monthly_salary_ = average_salary_ / kNumberOfMonths;
		return tax_rate_ * average_salary_ * population_ * employment_rate_;
	}

	double Nation::monthlyIncomeFromTradeDeals() const
	{
		const int NUMBER_OF_MONTHS = 12;
		double income = 0.0;

		for (std::vector<TradeDeal>::const_iterator deal = trade_deals_.begin(); deal != trade_deals_.end(); deal++)
		{
			income += deal->getValuePerAnnum() / NUMBER_OF_MONTHS;
		}

		return income;
	}

	void Nation::recieveTradeOffer(TradeDeal prospective_deal)
	{
		if (std::find(std::begin(trade_deals_), std::end(trade_deals_), prospective_deal) == std::end(trade_deals_))
		{
			trade_offers_.emplace(prospective_deal);
		};
	}

	void Nation::removeExpiredTradeDeals(const time_t &current_date)
	{
		for (std::vector<TradeDeal>::iterator offer = trade_deals_.begin(); offer != trade_deals_.end(); offer++)
		{
			if (offer->getExpiryDate() < current_date)
			{
				offer->setExpired();
			}
		}

		std::vector<TradeDeal>::iterator expired_deals = std::remove_if(
			trade_deals_.begin(), 
			trade_deals_.end(),
			[](TradeDeal deal) { return deal.isExpired(); });

		if (expired_deals != trade_deals_.end())
		{
			trade_deals_.erase(expired_deals, trade_deals_.end());
		}
	}

	std::string Nation::reportGlobalPercentageArea() const
	{
		return std::to_string(globalAreaPercentageControlled());
	}

	std::string Nation::reportRelationshipWithNation(Nation& another) const
	{
		if (nation_friendships.find(&another) != nation_friendships.end())
		{
			double relationship_score = nation_friendships.at(&another);
			if (relationship_score <= 0.2)
			{
				return "Enemy";
			}
			else if (relationship_score >= 0.7)
			{
				return "Ally";
			}
		}

		return "Neutral";
	}

	std::string Nation::reportString() const
	{
		return name_;
	}

	std::string Nation::reportTradeIncomeLastMonth() const
	{
		return std::to_string(finance_history_.getTradeIncomeLastMonth());
	}

	std::string Nation::reportTradeIncomeThisMonth() const
	{
		return std::to_string(monthlyIncomeFromTradeDeals());
	}

	std::string Nation::reportTradeIncomeLastYear() const
	{
		return std::to_string(finance_history_.getTradeIncomeLastYear());
	}

	std::string Nation::reportTradeIncomeThisYear() const
	{
		return std::to_string(finance_history_.getTradeIncomeThisYear());
	}

	void Nation::setRelationship(Nation* nation, double relationship_score)
	{
		std::pair<Nation*, double> relationship(nation, relationship_score);
		nation_friendships.emplace(relationship);
	}

	void Nation::setTaxRate(double tax_rate)
	{
		tax_rate_ = tax_rate;
	}


	void Nation::update(const time_t &current_date)
	{
		updateFinances(current_date);
		updateTradeDeals(current_date);
		updatePopulation();
	}

	void Nation::updateFinances(const time_t& current_date)
	{
		double monthly_profit = calculateMonthlyProfit();
		balance_ += monthly_profit;

		MonthlyFinanceHistory monthly_history(
			current_date,
			balance_,
			calculateMonthlyExpenses(),
			monthlyIncomeFromTax(),
			monthlyIncomeFromTradeDeals(),
			monthly_profit,
			calculateMonthlyIncome()
		);

		finance_history_.addMonthlyHistory(monthly_history);
	}

	void Nation::updatePopulation()
	{
		population_+= getNumberOfDeathsInTurn() + getNumberOfBirthsInTurn();
	}

	void Nation::updateTradeDeals(const time_t &current_date)
	{
		makeTradeDeals();
		removeExpiredTradeDeals(current_date);
	}

	bool Nation::operator==(const Nation & another)
	{
		return name_ == another.name_;
	}


}
