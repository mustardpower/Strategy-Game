#pragma once

#include <string>
#include <vector>

#include "SDL.h"
#include "SDL_ttf.h"

#include "MenuItem.h"
#include "SDL_TextRenderer.h"

template <class T>
class SDLMenu
{
private:
	int selectedMenuItemIndex;
	SDL_Window* parentWindow;
	std::vector<MenuItem<T>> menuItems;
	const int MENUITEM_POSX;
	const int MENUITEM_POSY;
	const int MENUITEM_HEIGHT;
public:
	SDLMenu(SDL_Window* parent, SDL_Rect clientArea);
	int getSelectedIndex() const;
	void addMenuItem(MenuItem<T> aMenuItem);
	bool containsPoint(SDL_Rect aRect, int x, int y);
	void handleClick(int x, int y);
	void nextMenuItem();
	void previousMenuItem();
	void renderMenu(SDL_Renderer* renderer);
	void selectCurrentItem();
	T selectedItem();
	SDL_Rect textLocationForIndex(TTF_Font* font, const int menuItemIndex);
};

template <typename T>
SDLMenu<T>::SDLMenu(SDL_Window*  parent, SDL_Rect clientArea) : 
	MENUITEM_POSX(clientArea.w * 0.2), 
	MENUITEM_POSY(clientArea.h * 0.3), 
	MENUITEM_HEIGHT(clientArea.h * 0.1)
{
	selectedMenuItemIndex = 0;
	parentWindow = parent;
}

template <typename T>
int SDLMenu<T>::getSelectedIndex() const
{
	return selectedMenuItemIndex;
}

template <typename T>
void SDLMenu<T>::addMenuItem(MenuItem<T> aMenuItem)
{
	menuItems.push_back(aMenuItem);
}

template<class T>
inline bool SDLMenu<T>::containsPoint(SDL_Rect aRect, int x, int y)
{
	if ((x >= aRect.x) && (x <= (aRect.x + aRect.w)))
	{
		if ((y >= aRect.y) && (y <= (aRect.y + aRect.h)))
		{
			return true;
		}
	}

	return false;
}

template<class T>
inline void SDLMenu<T>::handleClick(int x, int y)
{
	for (unsigned int i = 0; i < menuItems.size(); i++)
	{
		SDL_Rect textLocation = textLocationForIndex(SDL_TextRenderer::getFont(), i);
		// should already have cached text locations by this point??

		if (containsPoint(textLocation, x, y))
		{
			selectedMenuItemIndex = i;
			menuItems.at(i).invokeAction();
		}
	}
}

template <typename T>
void SDLMenu<T>::nextMenuItem()
{
	selectedMenuItemIndex = (selectedMenuItemIndex + 1) % menuItems.size();
}

template <typename T>
void SDLMenu<T>::previousMenuItem()
{
	selectedMenuItemIndex = (selectedMenuItemIndex - 1) % menuItems.size();
	if (selectedMenuItemIndex < 0)
	{
		selectedMenuItemIndex = menuItems.size() - 1;
	}
}

template <typename T>
void SDLMenu<T>::renderMenu(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xFF);
	SDL_RenderClear(renderer);

	int index = 0;
	SDL_Color textColor;

	TTF_Font* font = SDL_TextRenderer::getFont();
	if (!font) { return; }


	for (std::vector<MenuItem<T>>::const_iterator item = menuItems.cbegin(); item != menuItems.cend(); item++)
	{
		if (index == selectedMenuItemIndex)
		{
			textColor = { 0,255,0 };
		}
		else
		{
			textColor = { 255,0,0 };
		}

		SDL_TextRenderer::renderText(parentWindow, item->reportString(), textLocationForIndex(font, index), textColor);
		index++;
	}

	SDL_UpdateWindowSurface(parentWindow);
}

template<class T>
inline void SDLMenu<T>::selectCurrentItem()
{
	menuItems.at(selectedMenuItemIndex).invokeAction();
}

template<class T>
inline T SDLMenu<T>::selectedItem()
{
	return menuItems.at(selectedMenuItemIndex).getData();
}

template<class T>
inline SDL_Rect SDLMenu<T>::textLocationForIndex(TTF_Font* font, const int menuItemIndex)
{
	int w = 0;
	int h = 0;
	
	std::string text = (menuItems.at(menuItemIndex)).reportString();
	TTF_SizeText(font, text.c_str(), &w, &h);
	return SDL_Rect { MENUITEM_POSX, MENUITEM_POSY + (MENUITEM_HEIGHT * menuItemIndex), w, h };
}
