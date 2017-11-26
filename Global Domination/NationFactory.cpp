#include "NationFactory.h"

#include <fstream>
#include <string>


namespace global_domination
{
	void to_json(nlohmann::json& j, const Nation& nation) {
		j = nlohmann::json{ { "name", nation.getName() },{ "GDP", nation.getGDP() }, { "population", nation.getGDP() } };
	}

	void from_json(const nlohmann::json& j, Nation& nation) {
		nation = Nation(j.at("name").get<std::string>(), j.at("GDP").get<double>(), j.at("population").get<int>());
	}

	std::vector<Nation> NationFactory::createNations(std::string file_path)
	{
		std::ifstream i(file_path);

		Nation nation;
		std::vector<Nation> nations;

		nlohmann::json j;
		i >> j;
		for (nlohmann::json::iterator it = j.begin(); it != j.end(); ++it) 
		{
			from_json(*it, nation);
			nations.push_back(nation);
		}

		i.close();
		
		return nations;
	}

	void NationFactory::createJSONFile(std::vector<Nation> nations)
	{
		std::ofstream i("nations.json");
		if (i.is_open())
		{
			nlohmann::json json_nations(nations);
			i << json_nations << std::endl;
		}

		i.close();
	}
}
