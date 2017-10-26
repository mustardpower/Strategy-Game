#pragma once
#include <string>

namespace global_domination
{
	class Nation
	{
	private:
		std::string name;

	public:
		Nation() {};
		Nation(std::string aName);
		std::string getName() const;
		std::string reportString() const;
	};
}