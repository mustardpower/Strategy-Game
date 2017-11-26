#include "TradeResource.h"

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
}
