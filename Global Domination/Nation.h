#pragma once
#include <string>

namespace global_domination
{
	class Nation
	{
	public:
		Nation() {};
		Nation(std::string a_name);
		double calculateExpenses();
		double calculateIncome();
		double getBankBalance() const;
		std::string getName() const;
		unsigned int getNumberOfDeathsInTurn() const;
		unsigned int getNumberOfBirthsInTurn() const;
		std::string reportString() const;
		void update();
		void updateFinances();
		void updatePopulation();
	private:
		double bank_balance_;
		std::string name_;
		int population_;
	};
}