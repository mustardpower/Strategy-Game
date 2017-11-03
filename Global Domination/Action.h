#pragma once

namespace global_domination
{
	namespace TYPES
	{
		enum ACTION_LIST
		{
			MENU,
			NATION_SELECTION,
			INBOX,
			QUIT
		};
	};

	class IReciever
	{
	public:
		virtual void setAction(TYPES::ACTION_LIST action) = 0;
		virtual int getResult() = 0;
	};

	class Action
	{
	public:
		Action(IReciever *reciever) :p_receiver_(reciever) {}
		virtual int execute() = 0;
	protected:
		IReciever *p_receiver_;
	};

	class StartGameAction : public Action
	{
	public:
		StartGameAction(IReciever *reciever)
			: Action(reciever)
		{

		}

		int execute()
		{
			p_receiver_->setAction(TYPES::ACTION_LIST::NATION_SELECTION);
			return p_receiver_->getResult();
		}
	};

	class QuitGameAction : public Action
	{
	public:
		QuitGameAction(IReciever *reciever)
			: Action(reciever)
		{

		}

		int execute()
		{
			p_receiver_->setAction(TYPES::ACTION_LIST::QUIT);
			return p_receiver_->getResult();
		}
	};

	class NationSelectionAction : public Action
	{
	public:
		NationSelectionAction(IReciever *reciever)
			: Action(reciever)
		{

		}

		int execute()
		{
			p_receiver_->setAction(TYPES::ACTION_LIST::NATION_SELECTION);
			return p_receiver_->getResult();
		}
	};

	class OpenInboxAction : public Action
	{
	public:
		OpenInboxAction(IReciever *reciever)
			: Action(reciever)
		{

		}

		int execute()
		{
			p_receiver_->setAction(TYPES::ACTION_LIST::INBOX);
			return p_receiver_->getResult();
		}
	};
}