#pragma once

#include "MenuAction.h"

#include "SDL.h"

#include <memory>
#include <string>

using namespace std;

template <class T>
class MenuItem
{

private:
	shared_ptr<MenuAction> action;
	string text;
	SDL_Color textColor;
	T data;

public:
	string reportString() const;
	void invokeAction() const;
	T getData() const;

	MenuItem(string someText, shared_ptr<MenuAction> anAction, T menuItemData)
	{
		text = someText;
		action = anAction;
		data = menuItemData;
	}
};

template <typename T>
string MenuItem<T>::reportString() const
{
	return text;
}

template <typename T>
void MenuItem<T>::invokeAction() const
{
	action->Execute();
}

template<class T>
inline T MenuItem<T>::getData() const
{
	return data;
}
