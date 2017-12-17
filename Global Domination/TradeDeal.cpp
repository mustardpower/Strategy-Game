#include "TradeDeal.h"

#include "Nation.h"

namespace global_domination
{
	TradeDeal::TradeDeal(std::string payee)
	{
		payee_ = payee;
	}

	std::string TradeDeal::getPayee() const
	{
		return payee_;
	}

	void to_json(nlohmann::json& j, const TradeDeal& trade_deal) {
		j = nlohmann::json{ { "payee", trade_deal.getPayee() } };
	}

	void from_json(const nlohmann::json& j, TradeDeal& trade_deal) {
		trade_deal = TradeDeal(j.at("payee").get<std::string>());
	}
}
