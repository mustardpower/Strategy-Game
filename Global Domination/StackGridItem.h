#pragma once

#include "Action.h"

namespace global_domination
{
	template <class T>
	class StackGridItem
	{
	public:
		std::shared_ptr<Action> getAction();
		T* getData();
		std::shared_ptr<SDL_Rect> getTextLocation();
		void invokeAction() const;
		std::string reportString() const;
		void setTextLocation(SDL_Rect text_location);

		StackGridItem(std::string some_text, std::shared_ptr<Action> an_action, T menu_item_data)
		{
			text_ = some_text;
			action_ = an_action;
			data_ = menu_item_data;
		}

	private:
		std::shared_ptr<Action> action_;
		std::string text_;
		SDL_Color text_color_;
		std::shared_ptr<SDL_Rect> text_location_;
		T data_;
	};

	template<class T>
	inline std::shared_ptr<Action> StackGridItem<T>::getAction()
	{
		return std::shared_ptr<Action>();
	}

	template<class T>
	inline T * StackGridItem<T>::getData()
	{
		return NULL;
	}

	template<class T>
	inline std::shared_ptr<SDL_Rect> StackGridItem<T>::getTextLocation()
	{
		return std::shared_ptr<SDL_Rect>();
	}
	template<class T>
	inline void StackGridItem<T>::invokeAction() const
	{
	}
	template<class T>
	inline std::string StackGridItem<T>::reportString() const
	{
		return std::string();
	}
	template<class T>
	inline void StackGridItem<T>::setTextLocation(SDL_Rect text_location)
	{
	}
}