#include "Nation.h"
#include <fstream>

namespace global_domination
{
	Nation::Nation(std::string aName)
	{
		name_ = aName;
	}

	double Nation::calculateExpenses()
	{
		return 0.0;
	}

	double Nation::calculateIncome()
	{
		return 0.0;
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

	std::string Nation::reportString() const
	{
		return name_;
	}


	void Nation::update()
	{
		updateFinances();
		updatePopulation();
	}

	void Nation::updateFinances()
	{
		bank_balance_ += calculateIncome() - calculateExpenses();
	}

	void Nation::updatePopulation()
	{
		population_+= getNumberOfDeathsInTurn() + getNumberOfBirthsInTurn();
	}


}
