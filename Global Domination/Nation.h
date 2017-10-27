#pragma once
#include <string>

namespace global_domination
{
	class Nation
	{
	private:
		std::string name_;

	public:
		Nation() {};
		Nation(std::string a_name);
		std::string getName() const;
		std::string reportString() const;
	};
}