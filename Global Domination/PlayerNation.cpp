#include "PlayerNation.h"

namespace global_domination
{
	PlayerNation::PlayerNation(const Nation& nation, std::vector<Message>& messages) : Nation(nation), messages_(messages)
	{
	}
	void PlayerNation::removeExpiredTradeDeals(const time_t & current_date)
	{
		for (std::vector<TradeDeal>::iterator deal = trade_deals_.begin(); deal != trade_deals_.end(); deal++)
		{
			if (deal->getExpiryDate() < current_date)
			{
				deal->setExpired();
				messages_.push_back(Message("Trade deal has expired", "Your trade deal selling " + deal->getResource().getName() + " to " + deal->getPayee() + " has expired."));
			}
		}

		std::vector<TradeDeal>::iterator expired_deals = std::remove_if(
			trade_deals_.begin(),
			trade_deals_.end(),
			[](TradeDeal deal) { return deal.isExpired(); });

		if (expired_deals != trade_deals_.end())
		{
			trade_deals_.erase(expired_deals, trade_deals_.end());
		}
	}
}
