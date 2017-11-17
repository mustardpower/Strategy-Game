#pragma once
#include <string>

namespace global_domination
{
	class Nation
	{
	public:
		Nation() {};
		Nation(std::string a_name);
		std::string getName() const;
		unsigned int getNumberOfDeathsInTurn() const;
		unsigned int getNumberOfBirthsInTurn() const;
		std::string reportString() const;
		void update();
		void updatePopulation();
	private:
		std::string name_;
		int population_;
	};
}