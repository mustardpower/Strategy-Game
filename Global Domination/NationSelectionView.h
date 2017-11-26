#pragma once
#include "View.h"

#include "Nation.h"

namespace global_domination
{
	class NationSelectionView : public View
	{
	public:
		NationSelectionView::NationSelectionView(Game* the_game, SDL_Window * parent, SDL_Rect client_area);
		virtual ~NationSelectionView();
		Nation* getSelectedNation();
		void initialize();
		void onKeyDown();
		void onKeyUp();
		void onKeyPress(int keyCode);
		void respondToAction(TYPES::ACTION_LIST action);
		void updateSelectedNationDetails();
	private:
		std::vector<Nation> nations_;
	};
}