#define _CRT_SECURE_NO_WARNINGS

#include "TradeDeal.h"

#include "Nation.h"

namespace global_domination
{
	TradeDeal::TradeDeal(std::string trader, TradeResource resource, int quantity)
	{
		payee_ = trader;
		resource_ = resource;
		quantity_ = quantity;

		struct tm* time = new tm();
		time->tm_mon = 1;
		time->tm_mday = 1;
		time->tm_year = 120;
		expiry_date_ = mktime(time);
		delete time;
	}

	std::string TradeDeal::getPayee() const
	{
		return payee_;
	}

	TradeResource TradeDeal::getResource() const
	{
		return resource_;
	}

	double TradeDeal::getValuePerAnnum() const
	{
		return quantity_ * resource_.getUnitPrice();
	}

	std::string TradeDeal::reportExpiryDate() const
	{
		std::stringstream ss;
		ss << std::put_time(localtime(&expiry_date_), "%d %b %Y");
		return ss.str();
	}

	std::string TradeDeal::reportString() const
	{
		return getPayee() + " - " + resource_.getName();
	}

	std::string TradeDeal::reportTotalValue() const
	{
		double total_value = 0.0;
		return std::to_string(total_value);
	}

	std::string TradeDeal::reportValuePerAnnum() const
	{
		return std::to_string(getValuePerAnnum());
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
