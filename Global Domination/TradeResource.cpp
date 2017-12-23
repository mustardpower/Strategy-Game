#include "TradeResource.h"

#include <fstream>

namespace global_domination
{
	std::vector<TradeResource> TradeResource::resources_;

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

	std::string TradeResource::reportString() const
	{
		return getName();
	}

	// returns true if resource found and false if not
	bool TradeResource::find(std::string resource_name, TradeResource &matched_resource)
	{
		for (std::vector<TradeResource>::iterator resource = resources_.begin(); resource != resources_.end(); resource++)
		{
			if(resource->getName() == resource_name)
			{
				matched_resource = *resource;
				return true;
			}
		}
		return false;
	}

	void TradeResource::createTradeResources(std::string file_path)
	{
		std::ifstream i(file_path);

		TradeResource resource;	

		if (i.is_open())
		{
			nlohmann::json j;
			i >> j;
			for (nlohmann::json::iterator it = j.begin(); it != j.end(); ++it)
			{
				from_json(*it, resource);
				resources_.push_back(resource);
			}

			i.close();
		}
	}

	bool TradeResource::operator<(const TradeResource & another) const
	{
		return name_ < another.name_;
	}
	

}
