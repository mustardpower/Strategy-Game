#pragma once
#include "TradeResource.h"

#include "json.hpp"

namespace global_domination
{
	class TradeDeal
	{
	public:
		TradeDeal() {}
		TradeDeal(std::string trader, TradeResource resource, int quantity);
		std::string getPayee() const;
		TradeResource getResource() const;
		std::string reportString() const;

	private:
		std::string payee_;
		TradeResource resource_;
		int quantity_;
	};

	void to_json(nlohmann::json& j, const TradeDeal& trade_deal);
	void from_json(const nlohmann::json& j, TradeDeal& trade_deal);
}