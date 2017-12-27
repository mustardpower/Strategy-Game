#pragma once

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
			MOUSECLICK_LEFT,
			KEYPRESS_DOWN,
			KEYPRESS_UP,
			KEYPRESS_RETURN,
			NEXT_TURN,
			SELECTING_MESSAGE,
			SELECTING_NATION,
			SELECTING_RESOURCE,
			SELECTING_TRADE_DEAL,
			TRADEVIEW_ACCEPT_OFFER,
			TRADEVIEW_DECLINE_OFFER,
			TRADEVIEW_SHOW_OFFERS,
			TRADEVIEW_SHOW_DEALS,
			UNINITIALIZED,
			QUIT
		};
	};

	class IReciever
	{
	public:
		virtual ~IReciever() { };
		virtual void relayAction(TYPES::ACTION_LIST action) = 0;
	};
}