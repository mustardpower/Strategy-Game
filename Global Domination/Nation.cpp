#include "Nation.h"
#include <fstream>

namespace global_domination
{
	Nation::Nation(std::string aName)
	{
		name_ = aName;
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
		updatePopulation();
	}

	void Nation::updatePopulation()
	{
		population_+= getNumberOfDeathsInTurn() + getNumberOfBirthsInTurn();
	}
}
