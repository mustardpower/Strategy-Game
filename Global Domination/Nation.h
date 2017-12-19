#pragma once
#include <string>
#include <map>

#include "TradeDeal.h"
#include "TradeResource.h"

namespace global_domination
{
	class Nation
	{
	public:
		Nation() {};
		Nation(std::string a_name, double bank_balance, int population, std::map<TradeResource, int> resources);
		double calculateExpenses();
		double calculateIncome();
		double getGDP() const;
		double getGDPPerCapita() const;
		std::string getName() const;
		unsigned int getNumberOfDeathsInTurn() const;
		unsigned int getNumberOfBirthsInTurn() const;
		int getPopulation() const;
		std::vector<TradeDeal> getTradeDeals() const;
		std::map<TradeResource, int> getTradeResources() const;
		std::string reportString() const;
		void update();
		void updateFinances();
		void updatePopulation();

		bool operator == (const Nation& another);
	private:
		double GDP_;
		std::string name_;
		int population_;
		std::map<TradeResource, int> resources_;
		std::vector<TradeDeal> trade_deals_;
	};
}