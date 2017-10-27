#include "Nation.h"

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

	std::string Nation::reportString() const
	{
		return name_;
	}
}
