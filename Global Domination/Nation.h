#pragma once
#include <string>
#include <map>
#include <set>

#include "FinanceHistory.h"
#include "TradeDeal.h"
#include "TradeResource.h"

namespace global_domination
{
	class Nation
	{
	public:
		Nation() {};
		Nation(std::string a_name, double bank_balance, int population, std::map<TradeResource, int> resources, std::vector<TradeDeal> trade_deals);
		void acceptTradeOffer(TradeDeal trade_deal);
		void declineTradeOffer(TradeDeal trade_deal);
		std::vector<Nation*> alliedNations();
		double calculateMonthlyExpenses();
		double calculateMonthlyIncome();
		double calculateMonthlyProfit();
		void cancelTradeDeal(TradeDeal trade_deal);
		double getGDP() const;
		double getGDPPerCapita() const;
		std::vector<double> getMonthlyProfits(int number_of_months);
		std::string getName() const;
		unsigned int getNumberOfDeathsInTurn() const;
		unsigned int getNumberOfBirthsInTurn() const;
		int getPopulation() const;
		std::map<TradeResource, int> getTradeableResources();
		std::vector<TradeDeal> getTradeDeals() const;
		std::vector<TradeDeal> getTradeDealsForResource(TradeResource resource);
		std::vector<TradeDeal> getTradeOffersForResource(TradeResource resource);
		std::map<TradeResource, int> getTradeResources() const;
		void makeTradeDeals();
		void recieveTradeOffer(TradeDeal prospective_deal);
		std::string reportRelationshipWithNation(Nation& another) const;
		std::string reportString() const;
		void setRelationship(Nation* nation, double relationship_score);
		void update();
		void updateFinances();
		void updatePopulation();

		bool operator == (const Nation& another);
	private:
		double GDP_;
		FinanceHistory finance_history_;
		std::string name_;
		std::map<Nation*, double> nation_friendships;
		int population_;
		std::map<TradeResource, int> resources_;
		std::set<TradeDeal> trade_offers_;
		std::vector<TradeDeal> trade_deals_;
	};
}