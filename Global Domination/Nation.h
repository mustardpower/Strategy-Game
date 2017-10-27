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
		std::string reportString() const;
	private:
		std::string name_;
	};
}