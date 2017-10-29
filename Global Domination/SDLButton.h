#pragma once
#include <string>

#include "SDL.h"

namespace global_domination
{
	class SDLButton
	{
	public:
		SDLButton(SDL_Window* parent, std::string button_text, int pos_x, int pos_y);
		void render(SDL_Renderer* renderer);
	private:
		const int kPosX;
		const int kPosY;
		std::string button_text_;
		SDL_Window* parent_window_;
	};
}