#pragma once
#include "View.h"

namespace global_domination
{
	class InboxView : public View
	{
	public:
		InboxView::InboxView(std::shared_ptr<IReciever> reciever, SDL_Window * parent, SDL_Rect client_area);
		void initialize();
		void onKeyDown();
	private:
	};
}
