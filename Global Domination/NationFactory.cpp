#include "NationFactory.h"

#include <fstream>
#include <string>

namespace global_domination
{
	void to_json(nlohmann::json& j, const Nation& nation) {
		j = nlohmann::json{ { "name", nation.getName() },{ "GDP", nation.getGDP() }, { "population", nation.getGDP() }, { "resources", nation.getTradeResources()}};
	}

	void from_json(const nlohmann::json& j, Nation& nation) {

		std::map<TradeResource, int> resources;
		std::map<std::string, int> json_resources = j.at("resources").get<std::map<std::string, int>>();
		TradeResource* matching_resource = nullptr;

		std::vector<TradeResource*> trade_resources = TradeResource::createTradeResources("trade resources.json");
		for (std::map<std::string, int>::iterator pair = json_resources.begin(); pair != json_resources.end(); pair++)
		{
			for (std::vector<TradeResource*>::iterator resource = trade_resources.begin(); resource != trade_resources.end(); resource++)
			{
				if ((*resource)->getName() == pair->first)
				{
					matching_resource = *resource;
				}
				// find the resource with the name pair->first
			}

			if (matching_resource)
			{
				resources.emplace(std::pair<TradeResource, int>(*matching_resource, pair->second));
			}
		}

		nation = Nation(j.at("name").get<std::string>(), j.at("GDP").get<double>(), j.at("population").get<int>(), resources);
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
