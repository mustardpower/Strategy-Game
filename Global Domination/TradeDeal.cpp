#include "TradeDeal.h"

#include "Nation.h"

namespace global_domination
{
	TradeDeal::TradeDeal(std::string trader, TradeResource resource, int quantity)
	{
		payee_ = trader;
		resource_ = resource;
		quantity_ = quantity;
	}

	std::string TradeDeal::getPayee() const
	{
		return payee_;
	}

	TradeResource TradeDeal::getResource() const
	{
		return resource_;
	}

	std::string TradeDeal::reportString() const
	{
		return getPayee() + " - " + resource_.getName();
	}

	void to_json(nlohmann::json& j, const TradeDeal& trade_deal) {
		j = nlohmann::json{ { "payee", trade_deal.getPayee() } };
	}

	void from_json(const nlohmann::json& j, TradeDeal& trade_deal) {
		TradeResource resource;
		bool found = TradeResource::find(j.at("resource").get<std::string>(), resource);
		if (found)
		{
			trade_deal = TradeDeal(j.at("trader").get<std::string>(), resource, j.at("quantity").get<int>());
		}
	}
}
