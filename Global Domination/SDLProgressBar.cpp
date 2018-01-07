#include "SDLProgressBar.h"

namespace global_domination
{
	SDLProgressBar::SDLProgressBar(SDL_Window* parent, SDL_Rect client_area) : SDLControl(parent, client_area)
	{
		percent_complete_ = 0.0;
	}
	bool SDLProgressBar::handleClick(int, int)
	{
		return false;
	}
	void SDLProgressBar::render(SDL_Renderer * renderer)
	{
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xFF);
		SDL_RenderFillRect(renderer, &client_area_);

		SDL_SetRenderDrawColor(renderer, 0, 255, 0, 0xFF);
		SDL_Rect progress_bar_fill_area{ client_area_.x, client_area_.y, (int)(client_area_.w * percent_complete_), client_area_.h };
		SDL_RenderFillRect(renderer, &progress_bar_fill_area);

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xFF);
		SDL_RenderDrawRect(renderer, &client_area_);
	}
}

