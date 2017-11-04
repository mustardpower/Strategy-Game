#pragma once

#pragma once
#include <memory>
#include <string>

#include "SDL.h"

#include "SDLControl.h"

namespace global_domination
{
	class SDLStaticText : public SDLControl
	{
	public:
		SDLStaticText(SDL_Window* parent, std::string text, int pos_x, int pos_y);
		bool handleClick(int x, int y);
		void render(SDL_Renderer* renderer);
	private:
		const int kPosX;
		const int kPosY;
		std::string text_;
		SDL_Window* parent_;
	};
}