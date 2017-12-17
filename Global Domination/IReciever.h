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
			CHANGEVIEW_TRADE,
			MOUSECLICK_LEFT,
			KEYPRESS_DOWN,
			KEYPRESS_UP,
			KEYPRESS_RETURN,
			NEXT_TURN,
			SELECTING_MESSAGE,
			SELECTING_NATION,
			SELECTING_TRADE_DEAL,
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