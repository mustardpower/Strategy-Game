#pragma once

#include "SDLCompositePane.h"
#include "Game.h"
#include "Nation.h"

namespace global_domination
{
	enum PlotType
	{
		Unknown, Balance, Expenditure, Profit, TaxIncome, TradeDealIncome, Turnover
	};

	class FinancesView : public SDLCompositePane
	{
	public:
		FinancesView::FinancesView(std::shared_ptr<GameModel>, SDL_Window * parent, SDL_Rect client_area);
		virtual ~FinancesView();
		void addFinancesPlot();
		void addFinancesTabs();
		void addTaxDropDownList();
		void initialize();
		void respondToAction(Sint32 action);
		void updatePlot();
	private:
		Nation* nation_;
		PlotType current_plot_;
	};
}