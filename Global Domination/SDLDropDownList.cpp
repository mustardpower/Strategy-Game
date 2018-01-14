#include "SDLDropDownList.h"

namespace global_domination
{
	SDLDropDownList::SDLDropDownList(SDL_Window * parent, SDL_Rect client_area) : SDLControl(parent, client_area)
	{

	}

	bool SDLDropDownList::handleClick(int mouse_x, int mouse_y)
	{
		return false;
	}

	void SDLDropDownList::render(SDL_Renderer * renderer)
	{
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
		SDL_RenderFillRect(renderer, &client_area_);

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		SDL_RenderDrawRect(renderer, &client_area_);
	}
}

