#pragma once

#include <memory>
#include <string>

#include "SDL.h"

#include "Action.h"

namespace global_domination
{
	template <class T>
	class ListItem
	{
	public:
		std::shared_ptr<Action> getAction();
		T* getData();
		void invokeAction() const;
		std::string reportString() const;

		ListItem(std::string some_text, std::shared_ptr<Action> an_action, T menu_item_data)
		{
			text_ = some_text;
			action_ = an_action;
			data_ = menu_item_data;
		}

	private:
		std::shared_ptr<Action> action_;
		std::string text_;
		SDL_Color text_color_;
		T data_;
	};

	template <typename T>
	std::string ListItem<T>::reportString() const
	{
		return text_;
	}

	template <typename T>
	void ListItem<T>::invokeAction() const
	{
		action_->execute();
	}

	template<class T>
	inline std::shared_ptr<Action> ListItem<T>::getAction()
	{
		return action_;
	}

	template<class T>
	inline T* ListItem<T>::getData()
	{
		return &data_;
	}
}
