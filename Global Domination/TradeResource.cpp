#include "TradeResource.h"

#include <fstream>

namespace global_domination
{
	void to_json(nlohmann::json & j, const TradeResource & resource)
	{
		j = nlohmann::json{ { "name", resource.getName() },{ "price per unit", resource.getUnitPrice() },{ "edible", resource.isEdible() } };
	}

	void from_json(const nlohmann::json & j, TradeResource & resource)
	{
		resource = TradeResource(j.at("name").get<std::string>(), j.at("price per unit").get<double>(), j.at("edible").get<bool>());
	}
	
	TradeResource::TradeResource(std::string name, double unit_price, bool is_edible)
	{
		name_ = name;
		price_per_unit_ = unit_price;
		is_edible_ = is_edible;
	}

	std::string TradeResource::getName() const
	{
		return name_;
	}
	double TradeResource::getUnitPrice() const
	{
		return price_per_unit_;
	}

	bool TradeResource::isEdible() const
	{
		return is_edible_;
	}

	std::vector<TradeResource*> TradeResource::createTradeResources(std::string file_path)
	{
		std::ifstream i(file_path);

		TradeResource resource;
		std::vector<TradeResource*> resources;

		if (i.is_open())
		{
			nlohmann::json j;
			i >> j;
			for (nlohmann::json::iterator it = j.begin(); it != j.end(); ++it)
			{
				from_json(*it, resource);
				resources.push_back(new TradeResource(resource));
			}

			i.close();
		}

		return resources;
	}

	bool TradeResource::operator<(const TradeResource & another) const
	{
		return name_ < another.name_;
	}
	

}
