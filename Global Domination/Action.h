#pragma once

#include <memory>

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
			SELECTING_NATION,
			UNINITIALIZED,
			QUIT
		};
	};

	class IReciever
	{
	public:
		virtual ~IReciever() { };
		virtual void setAction(TYPES::ACTION_LIST action) = 0;
	};

	class Action
	{
	public:
		Action(std::shared_ptr<IReciever> reciever, TYPES::ACTION_LIST action) :p_receiver_(reciever), action_(action) {}
		~Action() { }
		void execute();
	protected:
		std::shared_ptr<IReciever> p_receiver_;
		TYPES::ACTION_LIST action_;

	};
}