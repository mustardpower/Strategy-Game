#pragma once

#include <memory>
#include <string>

#include "SDL.h"

#include "MenuAction.h"

namespace global_domination
{
	template <class T>
	class MenuItem
	{

	private:
		std::shared_ptr<MenuAction> action;
		std::string text;
		SDL_Color textColor;
		T data;

	public:
		std::string reportString() const;
		void invokeAction() const;
		T getData() const;

		MenuItem(std::string someText, std::shared_ptr<MenuAction> anAction, T menuItemData)
		{
			text = someText;
			action = anAction;
			data = menuItemData;
		}
	};

	template <typename T>
	std::string MenuItem<T>::reportString() const
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
}
