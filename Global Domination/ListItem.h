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
		std::shared_ptr<SDL_Rect> getTextLocation();
		void invokeAction() const;
		bool isUnread() const;
		void markAsRead();
		std::string reportString() const;
		void setTextLocation(SDL_Rect text_location);

		ListItem(std::string some_text, std::shared_ptr<Action> an_action, T menu_item_data)
		{
			text_ = some_text;
			action_ = an_action;
			data_ = menu_item_data;
			read_ = false;
		}

	private:
		std::shared_ptr<Action> action_;
		bool read_;
		std::string text_;
		SDL_Color text_color_;
		std::shared_ptr<SDL_Rect> text_location_;
		T data_;
	};

	template <typename T>
	std::string ListItem<T>::reportString() const
	{
		return text_;
	}

	template<class T>
	inline void ListItem<T>::setTextLocation(SDL_Rect text_location)
	{
		text_location_ = std::make_shared<SDL_Rect>(text_location);
	}

	template <typename T>
	void ListItem<T>::invokeAction() const
	{
		action_->execute();
	}

	template<class T>
	inline bool ListItem<T>::isUnread() const
	{
		return !read_;
	}

	template<class T>
	inline void ListItem<T>::markAsRead()
	{
		read_ = true;
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

	template<class T>
	inline std::shared_ptr<SDL_Rect> ListItem<T>::getTextLocation()
	{
		return text_location_;
	}
}
