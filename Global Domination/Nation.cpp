#include "Nation.h"
#include <fstream>

namespace global_domination
{
	Nation::Nation(std::string aName, double GDP, int population)
	{
		GDP_ = GDP;
		name_ = aName;
		population_ = population;
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
		GDP_ += calculateIncome() - calculateExpenses();
	}

	void Nation::updatePopulation()
	{
		population_+= getNumberOfDeathsInTurn() + getNumberOfBirthsInTurn();
	}


}
