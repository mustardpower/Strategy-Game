#pragma once
#include <string>

using namespace std;

class Nation
{
private:
	string name;

public:
	Nation(string aName);
	string getName() const;
	string reportString() const;
};