#pragma once
#include "SDLControl.h"

namespace global_domination
{
	class SDLDropDownList : public SDLControl
	{
	public:
		SDLDropDownList(SDL_Window* parent, SDL_Rect client_area);
		bool handleClick(int mouse_x, int mouse_y);
		void render(SDL_Renderer* renderer);
	};
}