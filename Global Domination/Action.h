#pragma once

#include <cstdint>

#include "IReciever.h"

namespace global_domination
{
	class Action
	{
	public:
		Action(TYPES::ACTION_LIST action);
		~Action() { }
		void execute();
	protected:
		TYPES::ACTION_LIST action_;
		uint32_t event_type_;
	};
}