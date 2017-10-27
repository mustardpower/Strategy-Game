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
	public:
		std::string reportString() const;
		void invokeAction() const;
		T getData() const;

		MenuItem(std::string some_text, std::shared_ptr<MenuAction> an_action, T menu_item_data)
		{
			text_ = some_text;
			action_ = an_action;
			data_ = menu_item_data;
		}

	private:
		std::shared_ptr<MenuAction> action_;
		std::string text_;
		SDL_Color text_color_;
		T data_;
	};

	template <typename T>
	std::string MenuItem<T>::reportString() const
	{
		return text_;
	}

	template <typename T>
	void MenuItem<T>::invokeAction() const
	{
		action_->execute();
	}

	template<class T>
	inline T MenuItem<T>::getData() const
	{
		return data_;
	}
}
