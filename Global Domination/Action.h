#pragma once

namespace global_domination
{
	namespace TYPES
	{
		enum ACTION_LIST
		{
			CHANGEVIEW_MENU,
			CHANGEVIEW_NATIONSELECTION,
			CHANGEVIEW_INBOX,
			MOUSECLICK_LEFT,
			KEYPRESS_DOWN,
			KEYPRESS_UP,
			KEYPRESS_RETURN,
			NEXT_TURN,
			OPEN_MENU,
			SELECTING_MESSAGE,
			SELECTING_NATION,
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

	class Action
	{
	public:
		Action(IReciever* reciever, TYPES::ACTION_LIST action) :p_receiver_(reciever), action_(action) {}
		~Action() { }
		void execute();
	protected:
		IReciever* p_receiver_;
		TYPES::ACTION_LIST action_;

	};
}