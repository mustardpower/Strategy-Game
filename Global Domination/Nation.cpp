#include "Nation.h"
#include <fstream>

namespace global_domination
{
	Nation::Nation(std::string aName, double GDP, int population, std::map<TradeResource, int> resources, std::vector<TradeDeal> trade_deals)
	{
		GDP_ = GDP;
		name_ = aName;
		population_ = population;
		resources_ = resources;
		trade_deals_ = trade_deals;
	}

	double Nation::calculateExpenses()
	{
		return 0.0;
	}

	double Nation::calculateIncome()
	{
		return 0.0;
	}

	double Nation::getGDP() const
	{
		return GDP_;
	}

	double Nation::getGDPPerCapita() const
	{
		if (population_ == 0) { return 0; }
		return (GDP_ / population_) * 1000000;
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

	std::vector<TradeDeal> Nation::getTradeDeals() const
	{
		return trade_deals_;
	}

	std::map<TradeResource, int> Nation::getTradeResources() const
	{
		return resources_;
	}

	void Nation::makeTradeDeals()
	{
	}

	std::string Nation::reportString() const
	{
		return name_;
	}


	void Nation::update()
	{
		updateFinances();
		makeTradeDeals();
		updatePopulation();
	}

	void Nation::updateFinances()
	{
		GDP_ += calculateIncome() - calculateExpenses();
	}

	void Nation::updatePopulation()
	{
		population_+= getNumberOfDeathsInTurn() + getNumberOfBirthsInTurn();
	}

	bool Nation::operator==(const Nation & another)
	{
		return name_ == another.name_;
	}


}
