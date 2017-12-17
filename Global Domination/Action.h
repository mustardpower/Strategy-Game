#pragma once

#include "IReciever.h"

namespace global_domination
{
	class Action
	{
	public:
		Action(IReciever* reciever, TYPES::ACTION_LIST action) :p_receiver_(reciever), action_(action) {}
		~Action() { }
		void execute();
	protected:
		IReciever* p_receiver_;
		TYPES::ACTION_LIST action_;

	};
}