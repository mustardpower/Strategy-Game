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
		Nation(std::string a_name, double bank_balance, int population, std::map<TradeResource, int> resources, std::vector<TradeDeal> trade_deals, double area);
		void acceptTradeOffer(TradeDeal trade_deal);
		void declineTradeOffer(TradeDeal trade_deal);
		std::vector<Nation*> alliedNations();
		double calculateMonthlyExpenses() const;
		double calculateMonthlyIncome() const;
		double calculateMonthlyProfit() const;
		void cancelTradeDeal(TradeDeal trade_deal);
		double getBalance() const;
		double getBalancePerCapita() const;
		double getLandArea() const;
		std::vector<double> getMonthlyBalanceHistory(int number_of_months);
		std::vector<double> getMonthlyExpenditureHistory(int number_of_months);
		std::vector<double> getMonthlyProfitsHistory(int number_of_months);
		std::vector<double> getMonthlyTurnoverHistory(int number_of_months);
		std::string getName() const;
		unsigned int getNumberOfDeathsInTurn() const;
		unsigned int getNumberOfBirthsInTurn() const;
		int getPopulation() const;
		double getTaxRate() const;
		std::map<TradeResource, int> getTradeableResources();
		std::vector<TradeDeal> getTradeDeals() const;
		std::vector<TradeDeal> getTradeDealsForResource(TradeResource resource);
		std::vector<TradeDeal> getTradeOffersForResource(TradeResource resource);
		std::map<TradeResource, int> getTradeResources() const;
		double globalAreaPercentageControlled() const;
		void makeTradeDeals();
		double monthlyIncomeFromTradeDeals() const;
		double monthlyIncomeFromTax() const;
		void recieveTradeOffer(TradeDeal prospective_deal);
		std::string reportGlobalPercentageArea() const;
		std::string reportRelationshipWithNation(Nation& another) const;
		std::string reportString() const;
		void setRelationship(Nation* nation, double relationship_score);
		void setTaxRate(double tax_rate);
		void update();
		void updateFinances();
		void updatePopulation();

		bool operator == (const Nation& another);
	private:
		double area_;
		double average_salary_;
		double balance_;
		double employment_rate_;
		FinanceHistory finance_history_;
		std::string name_;
		std::map<Nation*, double> nation_friendships;
		int population_;
		std::map<TradeResource, int> resources_;
		double tax_rate_;
		std::set<TradeDeal> trade_offers_;
		std::vector<TradeDeal> trade_deals_;
	};
}