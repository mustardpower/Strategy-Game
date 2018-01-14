#pragma once

#include <cstdint>

namespace global_domination
{
	namespace TYPES
	{
		enum ACTION_LIST
		{
			CHANGEVIEW_FINANCES,
			CHANGEVIEW_INBOX,
			CHANGEVIEW_MENU,
			CHANGEVIEW_NATIONSELECTION,
			CHANGEVIEW_RELATIONS,
			CHANGEVIEW_TRADE,
			CHANGEVIEW_WORLD,
			DECREASE_LISTBOX_VALUE,
			INCREASE_LISTBOX_VALUE,
			MOUSECLICK_LEFT,
			KEYPRESS_DOWN,
			KEYPRESS_UP,
			KEYPRESS_RETURN,
			NEXT_TURN,
			SELECTING_MESSAGE,
			SELECTING_NATION,
			SELECTING_RESOURCE,
			SELECTING_TRADE_DEAL,
			SHOW_BALANCE,
			SHOW_EXPENDITURE,
			SHOW_PROFIT,
			SHOW_TAX_INCOME,
			SHOW_TRADEDEAL_INCOME,
			SHOW_TURNOVER,
			TRADEVIEW_ACCEPT_OFFER,
			TRADEVIEW_CANCEL_DEAL,
			TRADEVIEW_DECLINE_OFFER,
			TRADEVIEW_SHOW_OFFERS,
			TRADEVIEW_SHOW_DEALS,
			UNINITIALIZED,
			QUIT
		};
	};

	class Action
	{
	public:
		Action(TYPES::ACTION_LIST action = TYPES::ACTION_LIST::UNINITIALIZED);
		~Action() { }
		void execute();
	private:
		TYPES::ACTION_LIST action_;
		static uint32_t event_type_;
	};
}