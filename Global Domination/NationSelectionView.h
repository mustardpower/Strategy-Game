#pragma once
#include "View.h"

#include "Nation.h"

namespace global_domination
{
	class NationSelectionView : public View
	{
	public:
		NationSelectionView::NationSelectionView(std::shared_ptr<IReciever> reciever, SDL_Window * parent, SDL_Rect client_area);
		virtual ~NationSelectionView();
		void initialize();
		void onKeyDown();
	private:
		std::vector<Nation> nations_;
	};
}