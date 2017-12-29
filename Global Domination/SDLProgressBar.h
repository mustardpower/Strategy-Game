#pragma once
#include "SDLControl.h"

namespace global_domination
{
	class SDLProgressBar : public SDLControl
	{
	public:
		SDLProgressBar(SDL_Window* parent, SDL_Rect client_area);
		bool handleClick(int, int);
		void render(SDL_Renderer* renderer);
	private:
		double percent_complete_;
	};
}
