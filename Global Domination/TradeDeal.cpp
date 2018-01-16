#define _CRT_SECURE_NO_WARNINGS

#include "TradeDeal.h"

#include "Nation.h"

namespace global_domination
{
	TradeDeal::TradeDeal(std::string trader, TradeResource resource, int quantity)
	{
		is_expired_ = false;
		payee_ = trader;
		resource_ = resource;
		quantity_ = quantity;
		value_per_annum_ = 0.0;

		struct tm* time = new tm();
		time->tm_mon = 1;
		time->tm_mday = 1;
		time->tm_year = 120;
		expiry_date_ = mktime(time);
		delete time;
	}

	time_t TradeDeal::getExpiryDate() const
	{
		return expiry_date_;
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

	bool TradeDeal::isExpired() const
	{
		return is_expired_;
	}

	std::string TradeDeal::reportExpiryDate() const
	{
		std::stringstream ss;
		ss << std::put_time(localtime(&expiry_date_), "%d %b %Y");
		return ss.str();
	}

	std::string TradeDeal::reportString() const
	{
		return getPayee();
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

	void TradeDeal::setExpired()
	{
		is_expired_ = true;
	}

	bool TradeDeal::operator<(const TradeDeal & another) const
	{
		return reportString() < another.reportString();
	}

	bool TradeDeal::operator==(const TradeDeal & another) const
	{
		if (payee_ != another.payee_) { return false; };
		if (resource_ != another.resource_) { return false; };

		return true;
	}

	bool TradeDeal::operator!=(const TradeDeal & another) const
	{
		return !(*this == another);
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
