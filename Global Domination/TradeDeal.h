#pragma once

#include "json.hpp"

namespace global_domination
{
	class TradeDeal
	{
	public:
		TradeDeal() {}
		TradeDeal(std::string payee);
		std::string getPayee() const;

	private:
		std::string payee_;
	};

	void to_json(nlohmann::json& j, const TradeDeal& trade_deal);
	void from_json(const nlohmann::json& j, TradeDeal& trade_deal);
}