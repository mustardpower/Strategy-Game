#pragma once

#include "Message.h"
#include "Nation.h"

namespace global_domination
{
	class PlayerNation : public Nation
	{
		public:
			PlayerNation(const Nation&, std::vector<Message>& messages);
			void removeExpiredTradeDeals(const time_t &current_date);

	private:
		std::vector<Message>& messages_;
	};
}