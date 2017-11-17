#include "Action.h"

namespace global_domination
{
	void Action::execute()
	{
		p_receiver_->relayAction(action_);
	}
}
