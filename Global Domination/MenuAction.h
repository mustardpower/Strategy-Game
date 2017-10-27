#pragma once

namespace global_domination
{
	namespace TYPES
	{
		enum ACTION_LIST
		{
			MENU,
			NATION_SELECTION,
			START_GAME,
			QUIT
		};
	};

	class IReciever
	{
	public:
		virtual void setAction(TYPES::ACTION_LIST action) = 0;
		virtual int getResult() = 0;
	};

	class MenuAction
	{
	protected:

		IReciever *p_receiver_;

	public:

		MenuAction(IReciever *reciever)
			:p_receiver_(reciever)
		{
		}

		virtual int execute() = 0;
	};

	class StartGameAction : public MenuAction
	{
	public:
		StartGameAction(IReciever *reciever)
			: MenuAction(reciever)
		{

		}

		int execute()
		{
			p_receiver_->setAction(TYPES::ACTION_LIST::START_GAME);
			return p_receiver_->getResult();
		}
	};

	class QuitGameAction : public MenuAction
	{
	public:
		QuitGameAction(IReciever *reciever)
			: MenuAction(reciever)
		{

		}

		int execute()
		{
			p_receiver_->setAction(TYPES::ACTION_LIST::QUIT);
			return p_receiver_->getResult();
		}
	};

	class NationSelectionAction : public MenuAction
	{
	public:
		NationSelectionAction(IReciever *reciever)
			: MenuAction(reciever)
		{

		}

		int execute()
		{
			p_receiver_->setAction(TYPES::ACTION_LIST::NATION_SELECTION);
			return p_receiver_->getResult();
		}
	};
}