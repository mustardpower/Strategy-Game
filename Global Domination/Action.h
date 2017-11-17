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
		Action(std::shared_ptr<IReciever> reciever) :p_receiver_(reciever) {}
		~Action() { }
		virtual void execute() = 0;
	protected:
		std::shared_ptr<IReciever> p_receiver_;
	};

	class QuitGameAction : public Action
	{
	public:
		QuitGameAction(std::shared_ptr<IReciever> reciever)
			: Action(reciever)
		{

		}

		void execute()
		{
			p_receiver_->setAction(TYPES::ACTION_LIST::QUIT);
		}
	};

	class NationSelectionAction : public Action
	{
	public:
		NationSelectionAction(std::shared_ptr<IReciever> reciever)
			: Action(reciever)
		{

		}

		void execute()
		{
			p_receiver_->setAction(TYPES::ACTION_LIST::SELECTING_NATION);
		}
	};

	class ChangeViewAction : public Action
	{
	public:
		ChangeViewAction(std::shared_ptr<IReciever> reciever, TYPES::ACTION_LIST new_view)
			: Action(reciever)
		{
			new_view_ = new_view;
		}

		void execute()
		{
			p_receiver_->setAction(new_view_);
		}

	private:
		TYPES::ACTION_LIST new_view_;
	};
}