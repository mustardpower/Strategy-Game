#include "FinancesView.h"

#include "SDLGraphPane.h"
#include "SDLStaticText.h"

namespace global_domination
{
	FinancesView::FinancesView(std::shared_ptr<GameModel> the_model, SDL_Window * parent, SDL_Rect client_area) : SDLCompositePane(parent, client_area)
	{
		nation_ = the_model->getSelectedNation();
	}

	FinancesView::~FinancesView()
	{
	}

	void FinancesView::initialize()
	{
		std::shared_ptr<SDLStaticText> title_label = std::make_shared<SDLStaticText>(parent_, "GDP: " + std::to_string(nation_->getGDP()), (int)(client_area_.w * 0.25), (int)(client_area_.h * 0.8));
		title_label->setId(FINANCES_BALANCE_LABEL);
		title_label->setFontSize(18);

		addChildControl(title_label);

		SDL_Rect graph_plot_client_area{ (int)(client_area_.w * 0.1), (int)(client_area_.h * 0.2), (int)(client_area_.w * 0.8), (int)(client_area_.h * 0.5) };
		std::shared_ptr<SDLGraphPane> finances_plot = std::make_shared<SDLGraphPane>(parent_, graph_plot_client_area);
		finances_plot->setFontSize(10);
		finances_plot->setId(FINANCES_PLOT);
		
		std::vector<std::string> month_names{ "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sept", "Oct", "Nov", "Dec" };
		finances_plot->setAxisLabelsX(month_names);

		addChildControl(finances_plot);
	}

	void FinancesView::respondToAction(Sint32 action)
	{
		switch (action)
		{
			case TYPES::ACTION_LIST::NEXT_TURN:
			{
				std::shared_ptr<SDLStaticText> control = std::dynamic_pointer_cast<SDLStaticText>(getChildControl(FINANCES_BALANCE_LABEL));
				control->setText("GDP: " + std::to_string(nation_->getGDP()));

				std::vector<double> columns{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };
				std::vector<double> monthly_profits{ 0, 100, 200, 300, 400, 500, 600, 700, 600, 500, 400, 300 };
				std::shared_ptr<SDLGraphPane> finances_plot = std::dynamic_pointer_cast<SDLGraphPane>(getChildControl(FINANCES_PLOT));
				finances_plot->setDataPoints(columns, monthly_profits);
			}
			break;
		}
	}
}
