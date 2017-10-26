#pragma once
#include <string>

using namespace std;

class Nation
{
private:
	string name;

public:
	Nation() {};
	Nation(string aName);
	string getName() const;
	string reportString() const;
};