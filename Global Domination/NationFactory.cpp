#include "NationFactory.h"

#include <fstream>
#include <string>

namespace global_domination
{
	void to_json(nlohmann::json& j, const Nation& nation) {
		j = nlohmann::json{ { "name", nation.getName() },{ "balance", nation.getBalance() }, { "population", nation.getPopulation() }, { "resources", nation.getTradeResources()},{ "area", nation.getLandArea() } };
	}

	void from_json(const nlohmann::json& j, Nation& nation) {

		TradeResource::createTradeResources("trade resources.json");
		nation = Nation(
			j.at("name").get<std::string>(),
			j.at("balance").get<double>(),
			j.at("population").get<int>(),
			getTradeResources(j),
			j.at("trade deals").get<std::vector<TradeDeal>>(),
			j.at("area").get<double>()
		);
	}

	void NationFactory::createNations(std::string file_path)
	{
		std::ifstream i(file_path);

		Nation nation;
		nlohmann::json j;
		i >> j;
		for (nlohmann::json::iterator it = j.begin(); it != j.end(); ++it) 
		{
			from_json(*it, nation);
			nations_.push_back(nation);
		}

		i.close();
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

	Nation* NationFactory::getNation(std::string name)
	{
		for (std::vector<Nation>::iterator it = nations_.begin(); it != nations_.end(); it++)
		{
			if(it->getName() == name)
			return &(*it);
		}

		return NULL;
	}

	std::vector<Nation> NationFactory::getNations()
	{
		return nations_;
	}

	std::map<TradeResource, int> getTradeResources(const nlohmann::json& json)
	{
		std::map<TradeResource, int> resources;
		std::map<std::string, int> json_resources = json.at("resources").get<std::map<std::string, int>>();

		TradeResource resource;
		for (std::map<std::string, int>::iterator pair = json_resources.begin(); pair != json_resources.end(); pair++)
		{

			bool matching_resource = TradeResource::find(pair->first, resource);
			if (matching_resource)
			{
				resources.emplace(std::pair<TradeResource, int>(resource, pair->second));
			}
		}

		return resources;
	}
}
