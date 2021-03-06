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
		std::string reportString() const;

		static bool find(std::string resource_name, TradeResource& resource);
		static void createTradeResources(std::string file_path);
		bool operator <(const TradeResource& another) const;
		bool operator == (const TradeResource &another) const;
		bool operator != (const TradeResource &another) const;
	private:
		static std::vector<TradeResource> resources_;
		std::string name_;
		double price_per_unit_;
		bool is_edible_;
	};

	void to_json(nlohmann::json& j, const TradeResource& resource);
	void from_json(const nlohmann::json& j, TradeResource& resource);
}