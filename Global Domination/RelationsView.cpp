#include "RelationsView.h"

#include "GameModel.h"
#include "SDLProgressBar.h"
#include "SDLDataGrid.h"

namespace global_domination
{
	RelationsView::RelationsView(std::shared_ptr<GameModel> the_model, SDL_Window * parent, SDL_Rect client_area) : SDLCompositePane(parent, client_area)
	{
	}

	RelationsView::~RelationsView()
	{
	}

	void RelationsView::initialize()
	{
		SDL_Rect progress_bar_client_area{ client_area_.x + client_area_.w * 0.3, client_area_.y + client_area_.h * 0.3, client_area_.w * 0.3, client_area_.h * 0.05 };
		std::shared_ptr<SDLProgressBar> progressBar = std::make_shared<SDLProgressBar>(parent_, progress_bar_client_area);
		addChildControl(progressBar);

		SDL_Rect resource_list_area{ client_area_.w * 0.06, client_area_.h * 0.3, client_area_.w * 0.88, client_area_.h * 0.6 };
		std::shared_ptr<SDLDataGrid<Nation, 2, 10>> data_grid = std::make_shared<SDLDataGrid<Nation, 2, 10>>(parent_, resource_list_area);

		Nation test_nation("Test Nation", 0.0, 2000, std::map<TradeResource, int>(), std::vector<TradeDeal>());
		std::shared_ptr<Action> null_action = std::make_shared<Action>(TYPES::ACTION_LIST::UNINITIALIZED);

		for (int col = 0; col < 2; col++)
		{
			for (int row = 0; row < 10; row++)
			{
				data_grid->addItem(StackGridItem<Nation>(null_action, test_nation), col, row);
			}
		}
		
		data_grid->setSelector(0, &Nation::reportSomething);
		data_grid->setSelector(1, &Nation::reportString);
		addChildControl(data_grid);
	}

	void RelationsView::respondToAction(Sint32 action)
	{
		
	}
}
