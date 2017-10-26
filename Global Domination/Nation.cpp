#include "Nation.h"

Nation::Nation(std::string aName)
{
	name = aName;
}

std::string Nation::getName() const
{
	return name;
}

std::string Nation::reportString() const
{
	return name;
}
