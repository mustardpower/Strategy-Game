#include "FinancesView.h"

#include "SDLDataGrid.h"
#include "SDLDropDownList.h"
#include "SDLGraphPane.h"
#include "SDLStaticText.h"
#include "SDLTabControl.h"

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
		SDL_Rect graph_plot_client_area{ (int)(client_area_.w * 0.02), (int)(client_area_.h * 0.13), (int)(client_area_.w * 0.75), (int)(client_area_.h * 0.5) };
		std::shared_ptr<SDLGraphPane> finances_plot = std::make_shared<SDLGraphPane>(parent_, graph_plot_client_area);
		finances_plot->setFontSize(10);
		finances_plot->setId(FINANCES_PLOT);
		
		std::vector<std::string> month_names{ "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sept", "Oct", "Nov", "Dec" };
		finances_plot->setAxisLabelsX(month_names);

		addChildControl(finances_plot);

		SDL_Rect data_grid_client_area{ (int)(client_area_.w * 0.02), (int)(client_area_.h * 0.75), (int)(client_area_.w * 0.75), (int)(client_area_.h * 0.2) };
		std::array<std::string, 5> header_names{ "Item", "This Month", "Last Month", "This Year", "Last Year" };
		std::shared_ptr<SDLDataGrid<Nation, 5, 5>> income_data_grid = std::make_shared<SDLDataGrid<Nation, 5,5>>(parent_, data_grid_client_area, header_names);
		income_data_grid->setFontSize(10);
		income_data_grid->showSliderBar(false);
		income_data_grid->setId(FINANCES_INCOME_DATA_GRID);
		income_data_grid->addItem("Trade Deals", 0, 0);

		std::array<std::string, 5> expenditure_header_names{ "Item", "This Month", "Last Month", "This Year", "Last Year" };

		std::shared_ptr<SDLDataGrid<Nation, 5, 5>> summary_data_grid = std::make_shared<SDLDataGrid<Nation, 5, 5>>(parent_, data_grid_client_area, header_names);
		summary_data_grid->setFontSize(10);
		summary_data_grid->showSliderBar(false);
		summary_data_grid->setId(FINANCES_EXPENSES_DATA_GRID);
		summary_data_grid->addItem("Turnover", 0, 0);
		summary_data_grid->addItem("Expenditure", 0, 0);
		summary_data_grid->addItem("Profit/Loss", 0, 0);
		summary_data_grid->addItem("Balance", 0, 0);

		std::shared_ptr<SDLDataGrid<Nation, 5, 5>> expenses_data_grid = std::make_shared<SDLDataGrid<Nation, 5, 5>>(parent_, data_grid_client_area, header_names);
		expenses_data_grid->setFontSize(10);
		expenses_data_grid->showSliderBar(false);
		expenses_data_grid->setId(FINANCES_EXPENSES_DATA_GRID);

		SDL_Rect tab_control_client_area{ (int)(client_area_.w * 0.02), (int)(client_area_.h * 0.75), (int)(client_area_.w * 0.75), (int)(client_area_.h * 0.2) };
		std::shared_ptr<SDLTabControl> finance_tabs = std::make_shared<SDLTabControl>(parent_, tab_control_client_area);
		finance_tabs->setFontSize(16);
		finance_tabs->addTab("Summary", summary_data_grid);
		finance_tabs->addTab("Expenses", expenses_data_grid);
		finance_tabs->addTab("Income", income_data_grid);
		addChildControl(finance_tabs);

		addLabel("Tax:", (int)(client_area_.w * 0.83), (int)(client_area_.h * 0.14), FINANCES_TAX_LABEL, 16);
		SDL_Rect tax_dropdown_client_area{ (int)(client_area_.w * 0.87), (int)(client_area_.h * 0.13), (int)(client_area_.w * 0.1), (int)(client_area_.h * 0.04) };
		std::shared_ptr<SDLDropDownList> tax_drop_down_list = std::make_shared<SDLDropDownList>(parent_, tax_dropdown_client_area);
		tax_drop_down_list->setFontSize(16);
		std::vector<std::string> items{ "0%", "5%", "10%", "15%", "20%"};
		tax_drop_down_list->setItems(items);
		addChildControl(tax_drop_down_list);

		updatePlot();
	}

	void FinancesView::respondToAction(Sint32 action)
	{
		switch (action)
		{
			case TYPES::ACTION_LIST::NEXT_TURN:
			{
				updatePlot();
			}
			break;
		}
	}
	void FinancesView::updatePlot()
	{
		std::vector<double> columns{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };
		const int kNumberOfMonths = 12;
		std::vector<double> monthly_profits = nation_->getMonthlyProfits(kNumberOfMonths);
		assert(monthly_profits.size() <= kNumberOfMonths);
		std::shared_ptr<SDLGraphPane> finances_plot = std::dynamic_pointer_cast<SDLGraphPane>(getChildControl(FINANCES_PLOT));
		finances_plot->setDataPoints(columns, monthly_profits);
	}
}
