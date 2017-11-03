#pragma once

namespace global_domination
{
	class SDLControl
	{
	public:
		virtual void handleClick(int mouse_x, int mouse_y) = 0;
		virtual void render(SDL_Renderer* renderer) = 0;
	};
}