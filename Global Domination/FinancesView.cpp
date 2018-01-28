#include "FinancesView.h"

#include "SDLDataGrid.h"
#include "SDLDropDownPlusMinusPane.h"
#include "SDLGraphPane.h"
#include "SDLStaticText.h"

namespace global_domination
{
	FinancesView::FinancesView(const GameModel& the_model, SDL_Window * parent, SDL_Rect client_area) : SDLCompositePane(parent, client_area), game_model_(the_model)
	{
		nation_ = the_model.getSelectedNation();
		current_plot_ = Turnover;
	}

	FinancesView::~FinancesView()
	{
		applyChanges();
	}

	void FinancesView::addExpenditureTab(std::shared_ptr<SDLTabControl> finance_tabs)
	{
		std::shared_ptr<SDLDataGrid<Nation, 5, 4>> expenses_data_grid = std::make_shared<SDLDataGrid<Nation, 5, 4>>(parent_, finance_tabs->getClientArea(), getGridHeaders());
		expenses_data_grid->setFontSize(10);
		expenses_data_grid->showSliderBar(false);
		expenses_data_grid->setId(FINANCES_EXPENSES_DATA_GRID);
		finance_tabs->addTab("Expenses", expenses_data_grid);
	}

	void FinancesView::addIncomeTab(std::shared_ptr<SDLTabControl> finance_tabs)
	{
		std::shared_ptr<SDLDataGrid<Nation, 5, 4>> income_data_grid = std::make_shared<SDLDataGrid<Nation, 5, 4>>(parent_, finance_tabs->getClientArea(), getGridHeaders());
		income_data_grid->setFontSize(10);
		income_data_grid->showSliderBar(false);
		income_data_grid->setId(FINANCES_INCOME_DATA_GRID);
		income_data_grid->addItem("Trade Deals", 0, 0, TYPES::ACTION_LIST::SHOW_TRADEDEAL_INCOME);
		income_data_grid->addItem("Taxes", 0, 0, TYPES::ACTION_LIST::SHOW_TAX_INCOME);

		std::shared_ptr<NoArgumentsGridCell<Nation>> cell_10 = std::make_shared<NoArgumentsGridCell<Nation>>(std::shared_ptr<Action>(), *nation_, &Nation::reportTradeIncomeThisMonth);
		income_data_grid->addItem(cell_10, 1, 0);

		std::shared_ptr<NoArgumentsGridCell<Nation>> cell_20 = std::make_shared<NoArgumentsGridCell<Nation>>(std::shared_ptr<Action>(), *nation_, &Nation::reportTradeIncomeLastMonth);
		income_data_grid->addItem(cell_20, 2, 0);

		std::shared_ptr<NoArgumentsGridCell<Nation>> cell_30 = std::make_shared<NoArgumentsGridCell<Nation>>(std::shared_ptr<Action>(), *nation_, &Nation::reportTradeIncomeThisYear);
		income_data_grid->addItem(cell_30, 3, 0);

		std::shared_ptr<NoArgumentsGridCell<Nation>> cell_40 = std::make_shared<NoArgumentsGridCell<Nation>>(std::shared_ptr<Action>(), *nation_, &Nation::reportTradeIncomeLastYear);
		income_data_grid->addItem(cell_40, 4, 0);

		std::shared_ptr<NoArgumentsGridCell<Nation>> cell_11 = std::make_shared<NoArgumentsGridCell<Nation>>(std::shared_ptr<Action>(), *nation_, &Nation::reportTaxIncomeThisMonth);
		income_data_grid->addItem(cell_11, 1, 1);

		std::shared_ptr<NoArgumentsGridCell<Nation>> cell_21 = std::make_shared<NoArgumentsGridCell<Nation>>(std::shared_ptr<Action>(), *nation_, &Nation::reportTaxIncomeLastMonth);
		income_data_grid->addItem(cell_21, 2, 0);

		std::shared_ptr<NoArgumentsGridCell<Nation>> cell_31 = std::make_shared<NoArgumentsGridCell<Nation>>(std::shared_ptr<Action>(), *nation_, &Nation::reportTaxIncomeThisYear);
		income_data_grid->addItem(cell_31, 3, 0);

		std::shared_ptr<NoArgumentsGridCell<Nation>> cell_41 = std::make_shared<NoArgumentsGridCell<Nation>>(std::shared_ptr<Action>(), *nation_, &Nation::reportTaxIncomeLastYear);
		income_data_grid->addItem(cell_41, 4, 0);

		finance_tabs->addTab("Income", income_data_grid);
	}

	void FinancesView::addSummaryTab(std::shared_ptr<SDLTabControl> finance_tabs)
	{
		std::shared_ptr<SDLDataGrid<Nation, 5, 4>> summary_data_grid = std::make_shared<SDLDataGrid<Nation, 5, 4>>(parent_, finance_tabs->getClientArea(), getGridHeaders());
		summary_data_grid->setFontSize(10);
		summary_data_grid->showSliderBar(false);
		summary_data_grid->setId(FINANCES_EXPENSES_DATA_GRID);
		summary_data_grid->addItem("Turnover", 0, 0, TYPES::ACTION_LIST::SHOW_TURNOVER);
		summary_data_grid->addItem("Expenditure", 0, 0, TYPES::ACTION_LIST::SHOW_EXPENDITURE);
		summary_data_grid->addItem("Profit/Loss", 0, 0, TYPES::ACTION_LIST::SHOW_PROFIT);
		summary_data_grid->addItem("Balance", 0, 0, TYPES::ACTION_LIST::SHOW_BALANCE);
		finance_tabs->addTab("Summary", summary_data_grid);

		using ActionPtr = std::shared_ptr<Action>;
		using NationCell = NoArgumentsGridCell<Nation>;
		using NationCellPtr = std::shared_ptr<NationCell>;

		NationCellPtr cell_10 = std::make_shared<NationCell>(ActionPtr(), *nation_, &Nation::reportIncomeThisMonth);
		summary_data_grid->addItem(cell_10, 1, 0);

		NationCellPtr cell_20 = std::make_shared<NationCell>(ActionPtr(), *nation_, &Nation::reportIncomeLastMonth);
		summary_data_grid->addItem(cell_20, 2, 0);

		NationCellPtr cell_30 = std::make_shared<NationCell>(ActionPtr(), *nation_, &Nation::reportIncomeThisYear);
		summary_data_grid->addItem(cell_30, 3, 0);

		NationCellPtr cell_40 = std::make_shared<NationCell>(ActionPtr(), *nation_, &Nation::reportIncomeLastYear);
		summary_data_grid->addItem(cell_40, 4, 0);

		NationCellPtr cell_11 = std::make_shared<NationCell>(ActionPtr(), *nation_, &Nation::reportExpenditureThisMonth);
		summary_data_grid->addItem(cell_11, 1, 1);

		NationCellPtr cell_21 = std::make_shared<NationCell>(ActionPtr(), *nation_, &Nation::reportExpenditureLastMonth);
		summary_data_grid->addItem(cell_21, 2, 1);

		NationCellPtr cell_31 = std::make_shared<NationCell>(ActionPtr(), *nation_, &Nation::reportExpenditureThisYear);
		summary_data_grid->addItem(cell_31, 3, 1);

		NationCellPtr cell_41 = std::make_shared<NationCell>(ActionPtr(), *nation_, &Nation::reportExpenditureLastYear);
		summary_data_grid->addItem(cell_41, 4, 1);

		NationCellPtr cell_12 = std::make_shared<NationCell>(ActionPtr(), *nation_, &Nation::reportProfitThisMonth);
		summary_data_grid->addItem(cell_12, 1, 1);

		NationCellPtr cell_22 = std::make_shared<NationCell>(ActionPtr(), *nation_, &Nation::reportProfitLastMonth);
		summary_data_grid->addItem(cell_22, 2, 1);

		NationCellPtr cell_32 = std::make_shared<NationCell>(ActionPtr(), *nation_, &Nation::reportProfitThisYear);
		summary_data_grid->addItem(cell_32, 3, 1);

		NationCellPtr cell_42 = std::make_shared<NationCell>(ActionPtr(), *nation_, &Nation::reportProfitLastYear);
		summary_data_grid->addItem(cell_42, 4, 1);

		NationCellPtr cell_13 = std::make_shared<NationCell>(ActionPtr(), *nation_, &Nation::reportBalance);
		summary_data_grid->addItem(cell_13, 1, 1);

	}

	void FinancesView::addFinancesPlot()
	{
		SDL_Rect graph_plot_client_area{ (int)(client_area_.w * 0.02), (int)(client_area_.h * 0.13), (int)(client_area_.w * 0.75), (int)(client_area_.h * 0.5) };
		std::shared_ptr<SDLGraphPane> finances_plot = std::make_shared<SDLGraphPane>(parent_, graph_plot_client_area);
		finances_plot->setFontSize(10);
		finances_plot->setId(FINANCES_PLOT);
		addChildControl(finances_plot);
	}

	void FinancesView::addFinancesTabs()
	{
		SDL_Rect tab_control_client_area{ (int)(client_area_.w * 0.02), (int)(client_area_.h * 0.75), (int)(client_area_.w * 0.75), (int)(client_area_.h * 0.2) };
		std::shared_ptr<SDLTabControl> finance_tabs = std::make_shared<SDLTabControl>(parent_, tab_control_client_area);
		finance_tabs->setFontSize(16);
		addSummaryTab(finance_tabs);
		addExpenditureTab(finance_tabs);
		addIncomeTab(finance_tabs);
		addChildControl(finance_tabs);
	}

	void FinancesView::addTaxDropDownList()
	{
		addLabel("Tax:", (int)(client_area_.w * 0.775), (int)(client_area_.h * 0.14), FINANCES_TAX_LABEL, 16);
		SDL_Rect tax_dropdown_client_area{ (int)(client_area_.w * 0.81), (int)(client_area_.h * 0.13), (int)(client_area_.w * 0.18), (int)(client_area_.h * 0.04) };
		std::shared_ptr<SDLDropDownPlusMinusPane> tax_drop_down_list = std::make_shared<SDLDropDownPlusMinusPane>(parent_, tax_dropdown_client_area);
		tax_drop_down_list->setFontSize(16);
		std::vector<std::string> items{ "0%", "5%", "10%", "15%", "20%" };
		tax_drop_down_list->setItems(items);
		tax_drop_down_list->setId(FINANCES_TAX_DROPDOWN_LIST);
		const double kTaxRate = nation_->getTaxRate();
		tax_drop_down_list->setText(std::to_string(kTaxRate) + "%");
		addChildControl(tax_drop_down_list);
	}

	void FinancesView::applyChanges()
	{
		std::shared_ptr<SDLDropDownPlusMinusPane> tax_dropdown_list = std::dynamic_pointer_cast<SDLDropDownPlusMinusPane>(getChildControl(FINANCES_TAX_DROPDOWN_LIST));
		const double tax_rate = std::stod(tax_dropdown_list->getText());
		if (nation_)
		{
			nation_->setTaxRate(tax_rate);
		}
	}

	std::array<std::string, 5> FinancesView::getGridHeaders()
	{
		return std::array<std::string, 5> { "Item", "This Month", "Last Month", "This Year", "Last Year" };
	}

	void FinancesView::initialize()
	{
		addFinancesPlot();
		addFinancesTabs();
		addTaxDropDownList();

		updatePlot();
	}

	void FinancesView::respondToAction(Sint32 action)
	{
		std::shared_ptr<SDLDropDownPlusMinusPane> tax_dropdown_list = std::dynamic_pointer_cast<SDLDropDownPlusMinusPane>(getChildControl(FINANCES_TAX_DROPDOWN_LIST));
		tax_dropdown_list->respondToAction(action);

		switch (action)
		{
			case TYPES::ACTION_LIST::SHOW_BALANCE:
			{
				current_plot_ = Balance;
			}
			break;
			case TYPES::ACTION_LIST::SHOW_EXPENDITURE:
			{
				current_plot_ = Expenditure;
			}
			break;
			case TYPES::ACTION_LIST::SHOW_PROFIT:
			{
				current_plot_ = Profit;
			}
			break;
			case TYPES::ACTION_LIST::SHOW_TAX_INCOME:
			{
				current_plot_ = TaxIncome;
			}
			break;
			case TYPES::ACTION_LIST::SHOW_TRADEDEAL_INCOME:
			{
				current_plot_ = TradeDealIncome;
			}
			break;
			case TYPES::ACTION_LIST::SHOW_TURNOVER:
			{
				current_plot_ = Turnover;
			}
			break;
		}

		updatePlot();
	}
	void FinancesView::updatePlot()
	{
		std::vector<double> columns{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };
		std::shared_ptr<SDLGraphPane> finances_plot = std::dynamic_pointer_cast<SDLGraphPane>(getChildControl(FINANCES_PLOT));
		const int kNumberOfMonths = 12;
		finances_plot->setAxisLabelsX(game_model_.getPreviousMonthNames(kNumberOfMonths));

		switch (current_plot_)
		{
			case Balance:
			{
				std::vector<double> balance_history = nation_->getMonthlyBalanceHistory(kNumberOfMonths);
				assert(balance_history.size() <= kNumberOfMonths);
				finances_plot->setDataPoints(columns, balance_history);
			}
			break;
			case Expenditure:
			{
				std::vector<double> monthly_expenses = nation_->getMonthlyExpenditureHistory(kNumberOfMonths);
				assert(monthly_expenses.size() <= kNumberOfMonths);
				finances_plot->setDataPoints(columns, monthly_expenses);
			}
			break;
			case Profit:
			{
				std::vector<double> monthly_profits = nation_->getMonthlyProfitsHistory(kNumberOfMonths);
				assert(monthly_profits.size() <= kNumberOfMonths);
				finances_plot->setDataPoints(columns, monthly_profits);
			}
			break;
			case TaxIncome:
			{
				std::vector<double> monthly_tax_income = nation_->getMonthlyTaxIncomeHistory(kNumberOfMonths);
				assert(monthly_tax_income.size() <= kNumberOfMonths);
				finances_plot->setDataPoints(columns, monthly_tax_income);
			}
			break;
			case TradeDealIncome:
			{
				std::vector<double> monthly_tradedeals_income = nation_->getMonthlyTradeDealsIncomeHistory(kNumberOfMonths);
				assert(monthly_tradedeals_income.size() <= kNumberOfMonths);
				finances_plot->setDataPoints(columns, monthly_tradedeals_income);
			}
			break;
			case Turnover:
			{
				std::vector<double> turnover_history = nation_->getMonthlyTurnoverHistory(kNumberOfMonths);
				assert(turnover_history.size() <= kNumberOfMonths);
				finances_plot->setDataPoints(columns, turnover_history);
			}
			break;
			default:
			{
				finances_plot->setDataPoints(columns, std::vector<double>());
			}
			break;
		}
	}
}
