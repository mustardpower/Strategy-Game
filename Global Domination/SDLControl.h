#pragma once
#include "SDL.h"

#include "ControlResources.h"

namespace global_domination
{
	class SDLControl
	{
	public:
		unsigned int getId();
		virtual bool handleClick(int mouse_x, int mouse_y) = 0;
		virtual void render(SDL_Renderer* renderer) = 0;
		void setId(ControlID id);
	private:
		ControlID id_;
	};
}