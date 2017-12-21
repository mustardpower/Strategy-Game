#pragma once

#include "StackGridItem.h"

namespace global_domination
{
	template <class T>
	class SDLStackGrid : public SDLControl
	{
	public:
		SDLStackGrid(SDL_Window* parent, SDL_Rect client_area, unsigned int items_x, unsigned int items_y);
		void addItem(StackGridItem<T> item, int location_x, int location_y);
		void clearItems();
		bool containsPoint(SDL_Rect aRect, int x, int y);
		bool handleClick(int x, int y);
		void render(SDL_Renderer* renderer);
	private:
		SDL_Rect client_area_;
	};

	template<class T>
	inline SDLStackGrid<T>::SDLStackGrid(SDL_Window * parent, SDL_Rect client_area, unsigned int items_x, unsigned int items_y) : SDLControl(parent)
	{
		client_area_ = client_area;
	}

	template<class T>
	inline void SDLStackGrid<T>::addItem(StackGridItem<T> item, int location_x, int location_y)
	{
	}

	template<class T>
	inline void SDLStackGrid<T>::clearItems()
	{
	}

	template<class T>
	inline bool SDLStackGrid<T>::containsPoint(SDL_Rect aRect, int x, int y)
	{
		return false;
	}

	template<class T>
	inline bool SDLStackGrid<T>::handleClick(int x, int y)
	{
		return false;
	}

	template<class T>
	inline void SDLStackGrid<T>::render(SDL_Renderer * renderer)
	{
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xFF);
		SDL_RenderFillRect(renderer, &client_area_);
	}
}
