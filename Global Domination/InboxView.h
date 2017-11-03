#pragma once
#include "View.h"

namespace global_domination
{
	class InboxView : public View
	{
	public:
		InboxView::InboxView(IReciever * reciever, SDL_Window * parent, SDL_Rect client_area);
		void initialize();
	private:
	};
}
