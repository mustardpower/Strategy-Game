#pragma once

#include <memory>
#include <vector>

#include "SDL.h"

#include "Action.h"
#include "SDLControl.h"

namespace global_domination
{
	class View
	{
	public:
		View(IReciever* reciever, SDL_Window* parent, SDL_Rect client_area);

		void addControl(std::shared_ptr<SDLControl> control);
		void handleClick(int mouse_x, int mouse_y);
		void render(SDL_Renderer* renderer);

	protected:
		IReciever* reciever_;
		SDL_Rect client_area_;
		SDL_Window* parent_;
	private:
		std::vector<std::shared_ptr<SDLControl>> controls_;
	};
}