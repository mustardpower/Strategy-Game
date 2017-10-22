#pragma once

namespace TYPES
{
	enum ACTION_LIST
	{
		START_GAME,
		SUBTRACT,
		MULTIPLY
	};
};

class IReciever
{
public:
	virtual void SetAction(TYPES::ACTION_LIST action) = 0;
	virtual int GetResult() = 0;
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
		pReciever_->SetAction(TYPES::ACTION_LIST::START_GAME);
		return pReciever_->GetResult();
	}
};

class SubtractCommand : public MenuAction
{
public:
	SubtractCommand(IReciever *reciever)
		: MenuAction(reciever)
	{

	}

	int Execute()
	{
		pReciever_->SetAction(TYPES::ACTION_LIST::SUBTRACT);
		return pReciever_->GetResult();
	}
};

class MultiplyCommand : public MenuAction
{
public:
	MultiplyCommand(IReciever *reciever)
		: MenuAction(reciever)
	{

	}

	int Execute()
	{
		pReciever_->SetAction(TYPES::ACTION_LIST::MULTIPLY);
		return pReciever_->GetResult();
	}
};