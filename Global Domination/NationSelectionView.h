#pragma once
#include "View.h"

#include "Nation.h"

namespace global_domination
{
	class NationSelectionView : public View
	{
	public:
		NationSelectionView::NationSelectionView(IReciever * reciever, SDL_Window * parent, SDL_Rect client_area);
		void initialize();
	private:
		std::vector<Nation> nations_;
	};
}