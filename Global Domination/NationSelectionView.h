#pragma once
#include "SDLCompositePane.h"

#include "GameModel.h"

namespace global_domination
{
	class Nation;

	class NationSelectionView : public SDLCompositePane
	{
	public:
		NationSelectionView::NationSelectionView(std::shared_ptr<GameModel> the_model, SDL_Window * parent, SDL_Rect client_area);
		virtual ~NationSelectionView();
		Nation* getSelectedNation();
		void initialize();
		void onKeyDown();
		void onKeyUp();
		void respondToAction(Sint32 action);
		void updateSelectedNationDetails();
	private:
		std::shared_ptr<GameModel> game_model_;
		std::vector<Nation> nations_;
	};
}