#pragma once

#include "SDLCompositePane.h"
#include "Game.h"
#include "SDLTabControl.h"

namespace global_domination
{
	enum PlotType
	{
		Unknown, Balance, Expenditure, Profit, TaxIncome, TradeDealIncome, Turnover
	};

	class Nation;

	class FinancesView : public SDLCompositePane
	{
	public:
		FinancesView::FinancesView(const GameModel& game_model, SDL_Window * parent, SDL_Rect client_area);
		virtual ~FinancesView();
		void addExpenditureTab(std::shared_ptr<SDLTabControl> finance_tabs);
		void addIncomeTab(std::shared_ptr<SDLTabControl> finance_tabs);
		void addSummaryTab(std::shared_ptr<SDLTabControl> finance_tabs);
		void addFinancesPlot();
		void addFinancesTabs();
		void addTaxDropDownList();
		void applyChanges();
		std::array<std::string, 5> getGridHeaders();
		void initialize();
		void respondToAction(Sint32 action);
		void updatePlot();
	private:
		const GameModel& game_model_;
		Nation* nation_;
		PlotType current_plot_;
	};
}