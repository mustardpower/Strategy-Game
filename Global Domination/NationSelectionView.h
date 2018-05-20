#pragma once
#include "SDLCompositePane.h"

#include "GameModel.h"

namespace global_domination
{
	class Nation;

	class NationSelectionView : public SDLCompositePane
	{
	public:
		NationSelectionView::NationSelectionView(GameModel& the_model, SDL_Window * parent, SDL_Rect client_area);
		virtual ~NationSelectionView();
		Nation* getSelectedNation();
		void addGameTurnsDropDownList();
		int getSelectedNumberOfTurns();
		void initialize();
		void onKeyDown();
		void onKeyUp();
		void respondToAction(Sint32 action);
		void updateSelectedNationDetails();
	private:
		GameModel& game_model_;
		std::vector<Nation> nations_;
	};
}