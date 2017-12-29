#include "Action.h"

#include "SDL.h"

namespace global_domination
{
	// only register a single custom event for all custom game actions
	// each event is then differentiated by its user code
	uint32_t Action::event_type_ = SDL_RegisterEvents(1);

	Action::Action(TYPES::ACTION_LIST action) : action_(action)
	{
	}

	void Action::execute()
	{
		if (event_type_ != ((Uint32)-1)) {
			SDL_Event event;
			SDL_memset(&event, 0, sizeof(event)); /* or SDL_zero(event) */
			event.type = event_type_;
			event.user.code = action_;
			event.user.data1 = 0;
			event.user.data2 = 0;
			SDL_PushEvent(&event);
		}
	}
}
