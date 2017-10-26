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

		IReciever *pReciever_;

	public:

		MenuAction(IReciever *reciever)
			:pReciever_(reciever)
		{
		}

		virtual int Execute() = 0;
	};

	class StartGameAction : public MenuAction
	{
	public:
		StartGameAction(IReciever *reciever)
			: MenuAction(reciever)
		{

		}

		int Execute()
		{
			pReciever_->setAction(TYPES::ACTION_LIST::START_GAME);
			return pReciever_->getResult();
		}
	};

	class QuitGameAction : public MenuAction
	{
	public:
		QuitGameAction(IReciever *reciever)
			: MenuAction(reciever)
		{

		}

		int Execute()
		{
			pReciever_->setAction(TYPES::ACTION_LIST::QUIT);
			return pReciever_->getResult();
		}
	};

	class NationSelectionAction : public MenuAction
	{
	public:
		NationSelectionAction(IReciever *reciever)
			: MenuAction(reciever)
		{

		}

		int Execute()
		{
			pReciever_->setAction(TYPES::ACTION_LIST::NATION_SELECTION);
			return pReciever_->getResult();
		}
	};
}