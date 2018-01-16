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
		time_t getExpiryDate() const;
		std::string getPayee() const;
		TradeResource getResource() const;
		double getValuePerAnnum() const;
		bool isExpired() const;
		std::string reportExpiryDate() const;
		std::string reportString() const;
		std::string reportTotalValue() const;
		std::string reportValuePerAnnum() const;
		void setExpired();
		bool operator<(const TradeDeal & another) const;
		bool operator==(const TradeDeal& another) const;
		bool operator!=(const TradeDeal& another) const;

	private:
		time_t expiry_date_;
		bool is_expired_;
		std::string payee_;
		int quantity_;
		TradeResource resource_;
		double value_per_annum_;
	};

	void to_json(nlohmann::json& j, const TradeDeal& trade_deal);
	void from_json(const nlohmann::json& j, TradeDeal& trade_deal);
}