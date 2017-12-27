
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

	double Nation::calculateMonthlyExpenses()
	{
		return 0.0;
	}

	double Nation::calculateMonthlyIncome()
	{
		double income = 0.0;
		const int NUMBER_OF_MONTHS = 12;

		for (std::vector<TradeDeal>::iterator deal = trade_deals_.begin(); deal != trade_deals_.end(); deal++)
		{
			income += deal->getValuePerAnnum() / NUMBER_OF_MONTHS;
		}
		return income;
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

	void Nation::recieveTradeOffer(TradeDeal prospective_deal)
	{
		trade_offers_.emplace(prospective_deal);
	}

	std::string Nation::reportString() const
	{
		return name_;
	}

	void Nation::setRelationship(Nation* nation, double relationship_score)
	{
		std::pair<Nation*, double> relationship(nation, relationship_score);
		nation_friendships.emplace(relationship);
	}


	void Nation::update()
	{
		updateFinances();
		makeTradeDeals();
		updatePopulation();
	}

	void Nation::updateFinances()
	{
		GDP_ += calculateMonthlyIncome() - calculateMonthlyExpenses();
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
