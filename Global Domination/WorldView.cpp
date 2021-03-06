#include "WorldView.h"

#include "GameModel.h"
#include "SDLProgressBar.h"
#include "SDLDataGrid.h"
#include "NoArgumentsGridCell.h"
#include "OneArgumentGridCell.h"

namespace global_domination
{
	WorldView::WorldView(GameModel& the_model, SDL_Window * parent, SDL_Rect client_area) : SDLCompositePane(parent, client_area), game_model_(the_model)
	{
	}

	WorldView::~WorldView()
	{
	}

	void WorldView::initialize()
	{
		const int kNumberOfGridRows = 10;
		const int kNumberOfGridColumns = 2;

		SDL_Rect progress_bar_client_area{ client_area_.x + (int)(client_area_.w * 0.3), client_area_.y + (int)(client_area_.h * 0.3), (int)(client_area_.w * 0.3), (int)(client_area_.h * 0.05) };
		std::shared_ptr<SDLProgressBar> progressBar = std::make_shared<SDLProgressBar>(parent_, progress_bar_client_area);
		addChildControl(progressBar);

		SDL_Rect relationship_list_area{ (int)(client_area_.w * 0.06), (int)(client_area_.h * 0.15), (int)(client_area_.w * 0.88), (int)(client_area_.h * 0.6) };
		std::array<std::string, kNumberOfGridColumns> header_names{ "Nation", "Area Controlled (%)" };
		std::shared_ptr<SDLDataGrid<Nation, kNumberOfGridColumns, kNumberOfGridRows>> data_grid = std::make_shared<SDLDataGrid<Nation, kNumberOfGridColumns, kNumberOfGridRows>>(parent_, relationship_list_area, header_names);

		std::vector<Nation*> nations = game_model_.getNations();
		std::shared_ptr<Action> null_action = std::make_shared<Action>(TYPES::ACTION_LIST::UNINITIALIZED);

		int row = 0;
		for (std::vector<Nation*>::iterator nation = nations.begin(); nation != nations.end(); nation++)
		{
			for (int col = 0; col < kNumberOfGridColumns; col++)
			{
				if (col == 0)
				{
					std::shared_ptr<NoArgumentsGridCell<Nation>> grid_cell = std::make_shared<NoArgumentsGridCell<Nation>>(null_action, **nation, &Nation::reportString);
					data_grid->addItem(grid_cell, col, row);
				}
				if (col == 1)
				{
					Nation* selected_nation = game_model_.getSelectedNation();
					std::shared_ptr<NoArgumentsGridCell<Nation>> grid_cell = std::make_shared<NoArgumentsGridCell<Nation>>(null_action, **nation, &Nation::reportGlobalPercentageArea);
					data_grid->addItem(grid_cell, col, row);
				}
			}

			row++;
		}

		addChildControl(data_grid);
	}

	void WorldView::respondToAction(Sint32 action)
	{

	}
}
