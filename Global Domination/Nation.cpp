#include "Nation.h"

Nation::Nation(string aName)
{
	name = aName;
}

string Nation::getName() const
{
	return name;
}

string Nation::reportString() const
{
	return name;
}
