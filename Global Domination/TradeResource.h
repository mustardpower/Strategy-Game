#pragma once

#include <string>

#include "json.hpp"

namespace global_domination
{
	class TradeResource
	{
	public:
		TradeResource() {}
		TradeResource(std::string name, double unit_price, bool is_edible);

		std::string getName() const;
		double getUnitPrice() const;
		bool isEdible() const;

		static std::vector<TradeResource*> createTradeResources(std::string file_path);
		bool operator <(const TradeResource& another) const;
	private:
		std::string name_;
		double price_per_unit_;
		bool is_edible_;
	};

	void to_json(nlohmann::json& j, const TradeResource& resource);
	void from_json(const nlohmann::json& j, TradeResource& resource);
}